#ifndef SLIM_HTTP_ROUTE_HANDLER_HPP
#define SLIM_HTTP_ROUTE_HANDLER_HPP

namespace slim_http
{

class request;
class response;

class route_handler
{
public:
    virtual ~route_handler() = default;
    virtual void prepare_response(const request &req, response &res) const = 0;
};

}
#endif // SLIM_HTTP_ROUTE_HANDLER_HPP
