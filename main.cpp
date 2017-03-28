#include <memory>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>

#include "server.hpp"
#include "response.hpp"
#include "string_body.hpp"
#include "string_response_body.hpp"
#include "file_response_body.hpp"

int main(int argc, char *argv[])
{
    boost::log::add_file_log("tst.log");
    boost::log::add_console_log(std::clog, boost::log::keywords::format = ">> %Message%");

    boost::asio::io_service service;

    slim_http::server server(service, 8080);

    server.add_GET_route_handler_func("/", [](const auto &req, auto &res){
        res.set_response_body(std::make_shared<slim_http::string_response_body>("result text"));
    });

    server.add_POST_route_handler_func<slim_http::string_body>("/", [](auto b, const auto &req, auto &res){
        res.set_response_body(std::make_shared<slim_http::string_response_body>("echo: " + b->get_string()));
    });

    server.add_GET_route_handler_func("/download_test_file", [](const auto &req, auto &res){
        res.set_response_body(std::make_shared<slim_http::file_response_body>("/home/alexey/ubuntu-16.10-server-amd64.iso"));
    });

    service.run();

    return 0;
}
