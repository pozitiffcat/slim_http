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
    }));
}

bool headers::has(const std::string &name)
{
    return std::find_if(_headers.begin(), _headers.end(), [name](const auto &p){
        return p.first == name;
    }) != _headers.end();
}

std::string headers::get(std::string &name)
{
    auto it = std::find_if(_headers.begin(), _headers.end(), [name](const auto &p){
        return p.first == name;
    });

    if (it == _headers.end())
        throw std::runtime_error("Header not found: " + name);

    return it->second;
}

}