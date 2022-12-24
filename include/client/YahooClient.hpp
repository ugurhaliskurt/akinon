#pragma once

#include "client/ClientBase.hpp"

#include <unordered_map>
#include <string>

class YahooClient : public ClientBase
{
private:
    void buildUrl(std::string& symbol) final;
    void setBaseUrl();
public:
    std::pair<std::string, double> getExchangeListBasedOnParameter(std::string &symbol);
};

