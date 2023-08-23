#include "ApiController.h"
// #include "RabbitMqController.h"
#include "Mongo.h"

void ApiController::createRabbitMq()
{
    // rabbitMqController = new RabbitMqController("10.113.18.249", 5672);

    // rabbitMqController->setapiController(this);
}

void ApiController::recieveTask()
{

    server.resource["^/create_project$"]["POST"] = [&](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
    {
        try
        {

            std::string sss = request->content.string();
            Json::Reader reader;
            Json::Value obj;
            reader.parse(sss, obj);
            std::string respo;

            Json::Value responseJ;
            std::cout << obj << "\n";
            try
            {
                //structure is as follows
                obj["site_id"]
                obj["layouts"] = []

                responseJ["errorCode"] = 1000;
                responseJ["messageText"] = "accepted";
            }
            catch (...)
            {

                responseJ["errorCode"] = 100;
                responseJ["messageText"] = "error request";

                std::cout << "error\n";
            }

            SimpleWeb::CaseInsensitiveMultimap header;
            header.emplace("Content-Type", "application/json");
            header.emplace("Access-Control-Allow-Origin", "*");
            header.emplace("Access-Control-Allow-Headers", "*");
            header.emplace("Access-Control-Allow-Methods", "*");
            Json::FastWriter fastwriter;
            std::string finalResp = fastwriter.write(responseJ);

            response->write(SimpleWeb::StatusCode::success_ok, finalResp, header);
        }
        catch (const std::exception &e)
        {
            std::cout << "\nin error\n";
            *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n"
                      << e.what();
        }
    };

    server.resource["^/testing$"]["POST"] = [&](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
    {
        try
        {

            std::string sss = request->content.string();
            Json::Reader reader;
            Json::Value obj;
            reader.parse(sss, obj);
            std::string respo;

            Json::Value responseJ;
            std::cout << obj << "\n";
            try
            {
               
                responseJ["errorCode"] = 1000;
                responseJ["messageText"] = "accepted";
            }
            catch (...)
            {

                responseJ["errorCode"] = 100;
                responseJ["messageText"] = "error request";

                std::cout << "error\n";
            }

            SimpleWeb::CaseInsensitiveMultimap header;
            header.emplace("Content-Type", "application/json");
            header.emplace("Access-Control-Allow-Origin", "*");
            header.emplace("Access-Control-Allow-Headers", "*");
            header.emplace("Access-Control-Allow-Methods", "*");
            Json::FastWriter fastwriter;
            std::string finalResp = fastwriter.write(responseJ);

            response->write(SimpleWeb::StatusCode::success_ok, finalResp, header);
        }
        catch (const std::exception &e)
        {
            std::cout << "\nin error\n";
            *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n"
                      << e.what();
        }
    };
}
int main()
{

    ApiController *apiController = new ApiController();
    while (true)
    {
        usleep(10000000);
    }
    return 0;
}