#include "SA_utils.h"

using std::vector;
using std::string;

std::vector<std::string> utils::splitString(std::string str, char delim) {
    vector<std::string> retVal = {};
    std::istringstream split(str);
    for (std::string each; std::getline(split, each, delim); retVal.push_back(each));
    return retVal;
}
int utils::indexOf(std::string str, char ch, int ignore) {
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ch) {
            if (i <= ignore) {
                continue;
            };
            return i;
        }
    }
    return -1;
}
int utils::lastIndexOf(std::string str, char ch) {
    int final = -1;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ch) {
            final = i;
        }
    }
    return final;
}