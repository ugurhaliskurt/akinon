#pragma once

#include <iostream>
//#include "../dbms/include/Dbms.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                       // JSON library
#include <cpprest/uri.h>                        // URI library
#include <cpprest/ws_client.h>                  // WebSocket client
#include <cpprest/containerstream.h>            // Async streams backed by STL containers
#include <cpprest/interopstream.h>              // Bridges for integrating Async streams with STL and WinRT streams
#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios

#include "Application.hpp"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

struct ClientData
{
    std::string stockName;
    int moneyTl;
};
class handler
{
    public:
        Application app;

        handler();
        handler(utility::string_t url);
        virtual ~handler();

        pplx::task<void>open(){return m_listener.open();}
        pplx::task<void>close(){return m_listener.close();}

        void on_initialize(const string& address);
        void on_shutdown();

    protected:

    private:
        void handle_get(http_request message);
        void handle_put(http_request message);
        void handle_post(http_request message);
        void handle_delete(http_request message);
        void handle_error(pplx::task<void>& t);
        void handle_options(http_request request);
        http_listener m_listener;

        std::multimap<std::string, ClientData> clientDataMap;
};

