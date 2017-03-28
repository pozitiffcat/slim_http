#ifndef SLIM_HTTP_BODY_HPP
#define SLIM_HTTP_BODY_HPP

#include <stddef.h>

namespace slim_http
{

class body
{
public:
    virtual ~body() = default;
    virtual void put_bytes(const char *data, size_t size) = 0;
};

}
#endif // SLIM_HTTP_BODY_HPP
