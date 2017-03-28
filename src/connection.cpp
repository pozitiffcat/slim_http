#include "request.hpp"
#include "response.hpp"
#include "connection.hpp"

namespace slim_http
{

slim_http::connection::connection(boost::asio::io_service &service, const routes &r)
    : _socket(service),
      _routes(r)
{
}

connection::~connection()
{
    BOOST_LOG_TRIVIAL(debug) << "connection stopped";
}

boost::asio::ip::tcp::socket &connection::get_socket()
{
    return _socket;
}

void connection::start()
{
    BOOST_LOG_TRIVIAL(debug) << "connection started";
    auto self = shared_from_this();

    auto req = std::make_shared<request>(_socket);
    req->start([this, req, self](auto e){
        if (!e)
        {
            auto res = std::make_shared<response>(_socket);

            // todo: read request body

            // todo: write response body

            res->start([this, res, self](auto e){
                if (e)
                {
                    BOOST_LOG_TRIVIAL(debug) << "response has error" << e.message();
                }
                else
                {
                    _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
                }
            });
        }
        else
        {
            BOOST_LOG_TRIVIAL(debug) << "request has error" << e.message();
        }
    });
}

}
