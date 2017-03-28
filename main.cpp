#include <memory>
#include <iostream>
#include <boost/log/utility/setup/console.hpp>

#include "body.hpp"
#include "server.hpp"
#include "body_route_handler.hpp"

class string_body : public slim_http::body
{
public:
    void put_bytes(const char *data, size_t size)
    {
        while (size--)
        {
            _str += *data++;
        }
    }

    const std::string &get_string() const
    {
        return _str;
    }

private:
    std::string _str;
};

class index_post_handler : public slim_http::body_route_handler
{
public:
    void prepare_response(const slim_http::body *body, const slim_http::request &req, slim_http::response &res) const
    {
        BOOST_LOG_TRIVIAL(debug) << "prepare response";
        auto str_body = static_cast<const string_body *>(body);
        BOOST_LOG_TRIVIAL(debug) << "str: " << str_body->get_string();
    }

    std::shared_ptr<slim_http::body> make_body() const
    {
        BOOST_LOG_TRIVIAL(debug) << "make body";
        return std::make_shared<string_body>();
    }
};

int main(int argc, char *argv[])
{
    boost::log::add_console_log(std::clog, boost::log::keywords::format = ">> %Message%");

    boost::asio::io_service service;

    slim_http::server server(service, 8080);

    auto _index_post_handler = std::make_shared<index_post_handler>();
    server.add_POST_route_handler("/", _index_post_handler);

    service.run();

    return 0;
}
