#ifndef STRUTILS_H
#define STRUTILS_H
#include <vector>
#include <string>

namespace str {

std::vector<std::string> split(const std::string &s, char delim);
std::string trim(std::string &str, std::string whitespaces = " \t");

template <class C>
std::string join(const C &container)
{
    std::string string;
    auto it = container.begin();
    for ( ; it != container.end() ; it++ )
        string += *it;
    
    return string;
}

template <class Iterator>
std::string join(Iterator begin, Iterator end, std::string sep = " ")
{
    std::string string;
    for ( auto it = begin ; it != end ; it++ )
    {
        string += *it;
        if (it + 1 != end)
            string += sep;
    }
    
    return string;
}

}
#endif // STRUTILS_H
