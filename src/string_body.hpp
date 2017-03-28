#ifndef SLIM_HTTP_STRING_BODY_HPP
#define SLIM_HTTP_STRING_BODY_HPP

#include <string>
#include "body.hpp"

namespace slim_http
{

class string_body : public slim_http::body
{
public:
    void put_bytes(const char *data, size_t size);
    const std::string &get_string() const;

private:
    std::string _str;
};

}
#endif // SLIM_HTTP_STRING_BODY_HPP
