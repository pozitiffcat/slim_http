#include <memory>
#include <iostream>
#include <boost/log/utility/setup/console.hpp>

#include "server.hpp"

int main(int argc, char *argv[])
{
    boost::log::add_console_log(std::clog, boost::log::keywords::format = ">> %Message%");

    boost::asio::io_service service;

    slim_http::server server(service, 8080);

    service.run();

    return 0;
}
