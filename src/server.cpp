#include "server.hpp"
#include "connection.hpp"

namespace slim_http
{

server::server(boost::asio::io_service &service, int port)
    : _acceptor(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4() , port))
{
    new_accept();
}

void server::new_accept()
{
    auto conn = std::make_shared<connection>(_acceptor.get_io_service(), _routes);

    _acceptor.async_accept(conn->get_socket(), [this, conn](auto e){
        if (!e)
        {
            BOOST_LOG_TRIVIAL(debug) << "accepted new connection";
            //this->new_accept();
            conn->start();
        }
        else
        {
            BOOST_LOG_TRIVIAL(debug) << "new connection has error" << e.message();
        }
    });
}

}
