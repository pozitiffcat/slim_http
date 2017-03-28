#ifndef SLIM_HTTP_HEADERS_HPP
#define SLIM_HTTP_HEADERS_HPP

#include <list>
#include <string>
#include <boost/optional.hpp>

namespace slim_http
{

class headers
{
public:
    void append(const std::string &name, const std::string &value);
    void replace(const std::string &name, const std::string &value);
    void remove_all(const std::string &name);
    boost::optional<std::string> get(const std::__cxx11::string &name) const;

private:
    std::list<std::pair<std::string, std::string>> _headers;
};

}
#endif // SLIM_HTTP_HEADERS_HPP
