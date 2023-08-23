#pragma once
#include <mutex>
#include <iostream>
#include "amqp.h"
#include "utils.h"
#include "amqp_tcp_socket.h"
#include <jsoncpp/json/json.h>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <functional>
#include "ApiController.h"

class RabbitMqController
{
public:
    RabbitMqController(char const *hName, int portL);

    ~RabbitMqController();

    void publishToQueue(char const *topic, int channel,  std::string sourceLocation);

    void listenToQueue(char const *queuename, int channel);

    void server_loop();

    void setapiController(ApiController *apiController)
    {

        std::cout<<"SETTING API CONTROLLER POINTER\n";
        _apiController = apiController;
    }

    bool getSensorFeedback()
    {
        return false;
    }

    /**
     * @brief
     *
     */
    void closeConnection();

    /**
     * @brief
     *
     */
    void startConnection();

public:
    ApiController *_apiController;
    std::thread server_thread;
    std::mutex socket_mutex;
    char const *LISTEN_QUEUE;
    char const *PUBLISH_QUEUE;
    char const *m_routingKey;
    char const *hostname;
    int port, status;
    amqp_socket_t *socket = NULL;
    amqp_connection_state_t conn;
    std::shared_ptr<std::thread> m_publishThread;
    std::shared_ptr<std::thread> m_listenThread;
    unsigned int m_channel_listen = 1;
    unsigned int m_channel_publish = 2;
    bool m_reset = false;
    bool m_startConnection = true;
};