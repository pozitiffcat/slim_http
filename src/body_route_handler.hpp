#ifndef SLIM_HTTP_BODY_ROUTE_HANDLER_HPP
#define SLIM_HTTP_BODY_ROUTE_HANDLER_HPP

#include <memory>

namespace slim_http
{

class body;
class request;
class response;

class body_route_handler
{
public:
    virtual ~body_route_handler() = default;
    virtual void prepare_response(const body *b, const request &req, response &res) const = 0;
    virtual std::shared_ptr<body> make_body() const = 0;
};

}
#endif // SLIM_HTTP_BODY_ROUTE_HANDLER_HPP
