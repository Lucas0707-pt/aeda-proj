#include "utils.h"
#include "sstream"

bool isNumeric(std::string& str)
{
    if (str.empty()) return false;
    return std::all_of(str.begin(),str.end(),[](char i){return isdigit(i);});
}

bool isFloat(std::string& str)
{
    std::istringstream iss(str);
    float f;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();
}


