#ifndef SLIM_HTTP_HEADERS_HPP
#define SLIM_HTTP_HEADERS_HPP

#include <list>
#include <string>

namespace slim_http
{

class headers
{
public:
    void append(const std::string &name, const std::string &value);
    void replace(const std::string &name, const std::string &value);
    void remove_all(const std::string &name);
    bool has(const std::string &name);
    std::string get(std::string &name);

private:
    std::list<std::pair<std::string, std::string>> _headers;
};

}
#endif // SLIM_HTTP_HEADERS_HPP
