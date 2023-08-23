#include "RabbitMqController.h"

RabbitMqController::RabbitMqController(char const *hName, int portL)
{

    hostname = hName;
    port = portL;
    m_reset = false;
    m_startConnection = true;
    server_thread = std::thread(&RabbitMqController::server_loop, this);
    // Fleet_Logger::LOG_INFO("RabbitMq:: Constructor");
    // static_cast<const char *>(XMLParser::ListenQueue.c_str());
    LISTEN_QUEUE = "FMS.CONFIRM-TASK";
    PUBLISH_QUEUE = "FMS.RECEIVE-TASK";
    m_routingKey = "AMR";
}

RabbitMqController::~RabbitMqController()
{
    m_startConnection = false;
    this->closeConnection();
    server_thread.join();
}

void RabbitMqController::publishToQueue(char const *topic, int channel, std::string sourceLocation)
{
    Json::Value obj;

    if (sourceLocation != "")
    {
        obj["taskId"] = "TEST";
        obj["sourceLocation"] = sourceLocation;
        obj["taskType"] = "MOVE";
    }
    else
    {
        obj["taskId"] = "TEST";
        obj["sourceLocation"] = sourceLocation;
        obj["taskType"] = "END";
    }

    Json::FastWriter fastWriter;
    std::string outputString;

    outputString = fastWriter.write(obj);

    die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

    amqp_basic_properties_t props;
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG | AMQP_BASIC_APP_ID_FLAG | AMQP_BASIC_MESSAGE_ID_FLAG;

    props.content_type = amqp_cstring_bytes("application/json");
    props.app_id = amqp_cstring_bytes("FMS");
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    uint64_t uniqueId = (uint64_t)ts.tv_sec * 1000000LL + (uint64_t)ts.tv_nsec / 1000LL;
    std::string uniqueIdStr = std::to_string(uniqueId);
    props.message_id = amqp_cstring_bytes(uniqueIdStr.c_str());

    props.delivery_mode = 2; /* persistent delivery mode */
    char char_array[outputString.length()];

    strcpy(char_array, outputString.c_str());
    die_on_error(amqp_basic_publish(conn, channel, amqp_cstring_bytes(PUBLISH_QUEUE),
                                    amqp_cstring_bytes(m_routingKey), 0, 0,
                                    &props, amqp_cstring_bytes(char_array)),
                 "Publishing");
};

void RabbitMqController::listenToQueue(char const *queuename, int channel)
{
    amqp_basic_consume(conn, m_channel_listen, amqp_cstring_bytes(queuename), amqp_empty_bytes,
                       0, 0, 0, amqp_empty_table);

    amqp_get_rpc_reply(conn);

    for (;;)
    {
        try
        {
            amqp_rpc_reply_t res;
            amqp_envelope_t envelope;

            amqp_maybe_release_buffers(conn);

            res = amqp_consume_message(conn, &envelope, NULL, 0);

            if (AMQP_RESPONSE_NORMAL != res.reply_type)
            {
                std::cout << "REPLY NOT NORMAL, EXITING AND STARTING AGAIN" << std::endl;
                m_reset = true;
                break;
            }

            if (envelope.message.properties._flags & AMQP_BASIC_CONTENT_TYPE_FLAG)
            {
            }

            Json::Reader reader;
            Json::Value obj;

            std::string s((const char *)envelope.message.body.bytes, envelope.message.body.len);

            reader.parse(s, obj);

            std::cout << "task status is " << obj["taskStatus"] << "\n";
            if (obj["taskStatus"].asInt() == 6)
            {

                // if(obj["sourceLocation"].asString() == );
                _apiController->glowPtl(obj["sourceLocation"].asString());
            }
            amqp_basic_ack(conn, m_channel_listen, envelope.delivery_tag, 0);

            amqp_destroy_envelope(&envelope);
            usleep(1000);
        }
        catch (const std::exception &e)
        {
            // Fleet_Logger::LOG_ERROR("RabbitMQ:: Task Error");
            std::cerr << e.what() << '\n';
        }
    }
}

void RabbitMqController::server_loop()
{
    this->startConnection();

    while (m_startConnection)
    {
        if (m_reset)
        {
            this->closeConnection();
            this->startConnection();
            m_reset = false;
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void RabbitMqController::startConnection()
{
    bool connected = false;
    while (!connected)
    {
        conn = amqp_new_connection();
        socket = amqp_tcp_socket_new(conn);

        if (!socket)
        {
            die("creating TCP socket");
        }

        status = amqp_socket_open(socket, hostname, port);

        if (status)
        {
            // Fleet_Logger::LOG_ERROR("RabbitMQ:: Connection Failed, Retrying...");
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
            die("opening TCP socket");
        }

        // Login with credentials
        die_on_amqp_error(amqp_login(conn, "/", 0, 131072, 10, AMQP_SASL_METHOD_PLAIN, "agv", "agv"), "Logging in");
        std::cout << "RABBIT MQ CONNECTED\n";
        connected = true;
    }

    // Fleet_Logger::LOG_INFO("RabbitMQ::Connected!");
    // Open the channel
    amqp_channel_open(conn, 1);
    die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel1");

    amqp_channel_open(conn, 2);
    die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel2");

    // Start the listen thread
    m_listenThread = std::make_shared<std::thread>(std::bind(&RabbitMqController::listenToQueue, this, LISTEN_QUEUE, 1));
}

void RabbitMqController::closeConnection()
{
    m_listenThread->join();

    try
    {
        amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        amqp_destroy_connection(conn);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
