#include "response.hpp"

namespace slim_http
{

response::response(boost::asio::ip::tcp::socket &socket)
    : _socket(socket)
{
}

void response::start(response::handler_func handler)
{
    auto self = shared_from_this();

    std::string str("HTTP/1.1 200 OK\r\n");

    _socket.async_write_some(boost::asio::buffer(str), [handler, self](auto e, auto t){
        if (!e)
            handler(boost::system::error_code());
        else
            handler(e);
    });
}

}
