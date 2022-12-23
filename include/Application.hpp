#pragma once

// C++ standard libs
#include <iostream>
#include <string>
#include <json.hpp>

#include "client/YahooClient.hpp"
#include "InteractionManager.hpp"

enum class Operation
{
    ExchangeRate=1,
    Exchange,
    ExchangeList
};

class Application
{
private:
    YahooClient yahooClient;
    InteractionManager interactionManager;
    std::vector<std::string> getCurrencies(std::string& targetsStr);
    std::vector<std::string> createSymbols(std::string& source, std::string& targetsStr);
public:
    nlohmann::json handleExchage(nlohmann::json& parsed_data);
    nlohmann::json handleExchageRate(nlohmann::json& parsed_data);
};