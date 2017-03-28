#include "routes.hpp"
#include "request.hpp"
#include "response.hpp"
#include "connection.hpp"
#include "route_handler.hpp"
#include "body_route_handler.hpp"

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
            auto response_handler = [this, res, self](auto e){
                if (e)
                {
                    BOOST_LOG_TRIVIAL(error) << "response has error" << e.message();
                }
                else
                {
                    _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
                }
            };

            if (req->method() == "GET")
            {
                auto opt_handler = _routes.get_GET_route_handler(req->path());

                if (opt_handler)
                {
                    auto handler = opt_handler.get();
                    handler->prepare_response(*req, *res);
                    res->start(response_handler);
                }
                else
                {
                    // todo: 404
                }
            }
            else if (req->method() == "POST")
            {
                auto opt_handler = _routes.get_POST_route_handler(req->path());

                if (opt_handler)
                {
                    auto handler = opt_handler.get();
                    auto body = handler->make_body();
                    req->write_body(body, [this, res, req, body, handler, response_handler, self](auto e){
                        if (!e)
                        {
                            handler->prepare_response(body.get(), *req, *res);
                            res->start(response_handler);
                        }
                        else
                        {
                            BOOST_LOG_TRIVIAL(error) << "request body has error" << e.message();
                        }
                    });
                }
                else
                {
                    // todo: 404
                }
            }
            else if (req->method() == "PUT")
            {
                auto opt_handler = _routes.get_PUT_route_handler(req->path());

                if (opt_handler)
                {
                    auto handler = opt_handler.get();
                    auto body = handler->make_body();
                    req->write_body(body, [this, res, req, handler, body, response_handler, self](auto e){
                        if (!e)
                        {
                            handler->prepare_response(body.get(), *req, *res);
                            res->start(response_handler);
                        }
                        else
                        {
                            BOOST_LOG_TRIVIAL(error) << "request body has error" << e.message();
                        }
                    });
                }
                else
                {
                    // todo: 404
                }
            }
            else if (req->method() == "DELETE")
            {
                auto opt_handler = _routes.get_DELETE_route_handler(req->path());

                if (opt_handler)
                {
                    auto handler = opt_handler.get();
                    handler->prepare_response(*req, *res);
                    res->start(response_handler);
                }
                else
                {
                    // todo: 404
                }
            }
        }
        else
        {
            BOOST_LOG_TRIVIAL(error) << "request has error" << e.message();
        }
    });
}

}
