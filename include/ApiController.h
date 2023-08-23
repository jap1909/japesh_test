#pragma once

#include <iostream>
#include "RESTServer/server_http.hpp"
#include "RESTServer/client_http.hpp"
#include <fstream>
#include <queue>
#include <unistd.h>
#include <jsoncpp/json/json.h>

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;
class RabbitMqController;
class ApiController
{
public:
    std::vector<std::string> tasks;
    std::string taskId = "";
    std::string location = "";
    std::map<std::string, std::string> mappingPicking;
    HttpServer server;

    std::thread server_thread;
    std::string _wcsIp = "";

    RabbitMqController *rabbitMqController;
    ApiController()
    {

        

        std::cout << "created rest controller";
        _wcsIp = "127.0.0.1";
        server.config.port = 9019;
        server_thread = std::thread(&ApiController::server_loop, this);
        // createRabbitMq();
        // char const *j = "127.0.0.1";
        recieveTask();
    }

    void server_loop()
    {
        std::cout << "server loop \n";
        //////////// added for pre_flight error response on web_browser    ------ ERROR "ERR_EMPTY_RESPONSE"////////////
        server.default_resource["OPTIONS"] = [&](std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
        {
            try
            {

                // Set header fields
                SimpleWeb::CaseInsensitiveMultimap header;
                header.emplace("Content-Type", "*");
                header.emplace("Access-Control-Allow-Origin", "*");
                header.emplace("Access-Control-Allow-Headers", "*");
                header.emplace("Access-Control-Allow-Methods", "*");
                response->write(SimpleWeb::StatusCode::success_ok, "", header);
            }
            catch (const std::exception &e)
            {
                response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
            }
        };

        server.start();
    }

    void createRabbitMq();

    void recieveTask();

    void glowPtl(std::string ptl)
    {

        try
        {
            // HttpClient client("10.113.11.13:6001");

            // Json::Value request;

            // request["owner"] = "Japesh";
            // request["callbackUrl"] = "http://10.113.19.45:9019/testing";

            // request["messages"][0]["position"] = location;
            // request["messages"][0]["color"] = "0xff0000";
            // request["messages"][0]["time"] = 400;
            // request["messages"][0]["ack"] = true;
            // request["messages"][0]["quantity"] = "2";
            // request["messages"][0]["crate"] = "5435";
            // request["messages"][0]["response"] = true;

            // // request["data"] = ptl;

            // Json::FastWriter fastwriter;
            // std::string finalResp = fastwriter.write(request);

            // Json::Reader reader;
            // Json::Value obj;

            // std::cout << "calling own api\n";

            // auto response = client.request("POST", "/rapido/api/quantity", finalResp);
            // std::string sss = response->content.string();
            // reader.parse(sss, obj);
        }
        catch (const SimpleWeb::system_error &e)
        {
            // cerr << "Client request error: " << e.what() << endl;
        }
    }
    bool completeTask()
    {

        // _db->update()
        // TaskCompletionResponse resp;
        // try
        // {
        //     HttpClient client(_wcsIp);
        //     Json::Reader reader;
        //   try
        // {
        //     HttpClient client(_wcsIp);
        //     Json::Reader reader;
        //     Json::Value obj;

        //     auto response = client.request("POST", path, req.getJsonString());
        //     std::string sss = response->content.string();
        //     reader.parse(sss, obj);

        //     resp.error.message = obj["errorMessage"].asString();
        //     resp.error.code = obj["errorCode"].asInt();
        // }
        // catch (const SimpleWeb::system_error &e)
        // {
        //     cerr << "Client request error: " << e.what() << endl;
        // }  Json::Value obj;

        //     auto response = client.request("POST", path, req.getJsonString());
        //     std::string sss = response->content.string();
        //     reader.parse(sss, obj);

        //     resp.error.message = obj["errorMessage"].asString();
        //     resp.error.code = obj["errorCode"].asInt();
        // }
        // catch (const SimpleWeb::system_error &e)
        // {
        //     cerr << "Client request error: " << e.what() << endl;
        // }
        return true;
    }
};
