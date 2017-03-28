#ifndef SLIM_HTTP_RESPONSE_BODY_HPP
#define SLIM_HTTP_RESPONSE_BODY_HPP

#include <vector>
#include <stddef.h>

namespace slim_http
{

class response;

class response_body
{
public:
    virtual ~response_body() = default;
    virtual void prepare_response(response &res) const = 0;
    virtual const std::vector<char> get_next_part(size_t size) = 0;
    virtual size_t get_content_length() const = 0;
};

}
#endif // SLIM_HTTP_RESPONSE_BODY_HPP
