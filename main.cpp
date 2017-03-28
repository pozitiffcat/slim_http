#include <memory>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>

#include "server.hpp"
#include "response.hpp"
#include "string_body.hpp"
#include "string_response_body.hpp"
#include "file_response_body.hpp"
#include "route_handler.hpp"
#include "body_route_handler.hpp"

class index_post_handler : public slim_http::body_route_handler
{
public:
    void prepare_response(const slim_http::body *body, const slim_http::request &req, slim_http::response &res) const
    {
        auto str_body = static_cast<const slim_http::string_body *>(body);
    }

    std::shared_ptr<slim_http::body> make_body() const
    {
        return std::make_shared<slim_http::string_body>();
    }
};

class index_get_handler : public slim_http::route_handler
{
public:
    void prepare_response(const slim_http::request &req, slim_http::response &res) const
    {
        res.set_response_body(std::make_shared<slim_http::string_response_body>("result text"));
    }
};

class file_get_handler : public slim_http::route_handler
{
public:
    void prepare_response(const slim_http::request &req, slim_http::response &res) const
    {
        res.set_response_body(std::make_shared<slim_http::file_response_body>("/home/alexey/ubuntu-16.10-server-amd64.iso"));
    }
};

int main(int argc, char *argv[])
{
    boost::log::add_file_log("tst.log");
    boost::log::add_console_log(std::clog, boost::log::keywords::format = ">> %Message%");

    boost::asio::io_service service;

    slim_http::server server(service, 8080);

    auto _index_get_handler = std::make_shared<index_get_handler>();
    server.add_GET_route_handler("/", _index_get_handler);

    auto _index_post_handler = std::make_shared<index_post_handler>();
    server.add_POST_route_handler("/", _index_post_handler);

    auto _file_get_handler = std::make_shared<file_get_handler>();
    server.add_GET_route_handler("/f", _file_get_handler);

    service.run();

    return 0;
}
