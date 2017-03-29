#ifndef SLIM_HTTP_ASYNC_TOKEN_HPP
#define SLIM_HTTP_ASYNC_TOKEN_HPP

#include <functional>

namespace slim_http
{

class async_token
{
public:
    typedef std::function<void()> handler_func;

public:
    void handle();
    void set_handler(handler_func handler);

private:
    handler_func _handler;
};

}
#endif // SLIM_HTTP_ASYNC_TOKEN_HPP
