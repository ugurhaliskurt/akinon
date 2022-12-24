#pragma once
#include <string>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <chrono>

inline bool string_replace(std::string& str, const std::string from, const std::string to)
{
    size_t start = str.find(from);
    if(start == std::string::npos)
    {
        return false;
    }
    str.replace(start, from.length(), to);
    return true;
}

inline size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{ 
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

inline std::unordered_map< std::string, double > convertDateValueMap(std::string &str)
{
    std::unordered_map< std::string, double > result;
    std::istringstream f(str);
    std::string line;
    getline(f, line); // first line is headers do not read
    while( true )
    {
        if( !getline(f, line) ) break;
        // simple split (alternatively, use strtok)
        std::string key = line.substr(0,line.find(',')); //date
        line.substr(line.find(',')+1); //Open
        line.substr(line.find(',')+1); //High
        line.substr(line.find(',')+1); //low
        std::string value = line.substr(line.find(',')+1); //Close
        result[key] = std::stod(value);     
    }
    return result;
}

inline std::string yearMonthDayDateNow()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);
    std::string yearMonthDay = std::to_string( local_tm.tm_year + 1900 ) + ("-") + 
                                std::to_string( local_tm.tm_mon + 1 ) + ("-") + 
                                std::to_string( local_tm.tm_mday );

    std::cout << yearMonthDay << std::endl;
    return yearMonthDay;
}