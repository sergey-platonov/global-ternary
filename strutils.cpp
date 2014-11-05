#include "strutils.h"
#include <sstream>

namespace str {

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string trim(std::string &str, std::string whitespaces)
{
    size_t i = str.find_first_not_of(whitespaces);
    if (i != 0)
    {
        str.erase( 0, i );
    }
    i = str.find_last_not_of(whitespaces);
    if (i != str.length() - 1)
    {    
        str.erase( i+1, str.npos );
    }
    return str;
}

}
