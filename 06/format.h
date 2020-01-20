#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <iostream>

template<class T>
std::string any2str(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

std::vector<std::string> parseArgs() {
    return {};
}

template<class First, class... Rest>
std::vector<std::string> parseArgs(First first, Rest... rest) {
    auto args = parseArgs(rest...);
    args.push_back(any2str(first));
    return args;
}

template<class... Args>
std::string format(std::string str, Args... input){
    auto args = parseArgs(input...);
    assert(args.size() == sizeof...(input));

    int n = args.size();
    std::stringstream ss(str), result;
    std::string tmp;

    char ltok = '{';
    char rtok = '}';
    while(std::getline(ss, tmp, ltok)){
        result << tmp;
        int index;
        ss >> index;
        if (index < 0)
        	throw std::runtime_error ("invalid argument");
        if(ss.peek() != rtok)
            throw std::runtime_error ("error format");
        else
            ss.ignore();
        if(index < n)
            result << args[n - 1 - index];
        else
            throw std::runtime_error ("something is wrong");
    }
    return result.str();
}