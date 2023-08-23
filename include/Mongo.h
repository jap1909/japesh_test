#pragma once

#include <iostream>
#include <vector>
// Mongo includes
#include <bsoncxx/json.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/types.hpp>
#include <unistd.h>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

class MongoDB
{
public:
    /**
     * @brief Construct a new Mongo DB object
     *
     */
    MongoDB(std::string mongoIP, std::string databaseName)
    {
        // This should be done only once.
        bool connected = false;
        while (!connected)
        {
            try
            {
                mongocxx::instance instance{};
                uri = mongocxx::uri(mongoIP);
                client = mongocxx::client(uri);
                database = client[databaseName];
                connected = true;
                break;
            }
            catch (...)
            {
                std::cout << "mongo db not connected\n";
            }
            usleep(1000000);
        }

        // Create the "general" collection if it doesn't already exist
        if (!database.has_collection("project"))
        {
            database.create_collection("general");
        }
    }

    ~MongoDB()
    {
        std::cout << "ending mongo\n";
    }

private:
    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database database;
};