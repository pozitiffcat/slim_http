#include <algorithm>
#include <stdexcept>
#include "headers.hpp"

namespace slim_http
{

void headers::append(const std::string &name, const std::string &value)
{
    _headers.push_back(std::make_pair(name, value));
}

void headers::replace(const std::string &name, const std::string &value)
{
    remove_all(name);
    append(name, value);
}

void headers::remove_all(const std::string &name)
{
    _headers.erase(std::remove_if(_headers.begin(), _headers.end(), [name](const auto &p){
        return p.first == name;
    }), _headers.end());
}

boost::optional<std::string> headers::get(const std::string &name) const
{
    auto it = std::find_if(_headers.begin(), _headers.end(), [name](const auto &p){
        return p.first == name;
    });

    if (it == _headers.end())
        return boost::none;
    else
        return it->second;
}

const std::list<std::pair<std::string, std::string> > &headers::get_pair_list() const
{
    return _headers;
}

}
