#pragma once

#include "string"
#include <json.hpp>

struct Transaction
{
    std::string id;
    std::string date;
    nlohmann::json data;
};

class InteractionManager
{
private:
    std::string genereteIngeractionId();
    std::multimap<std::string, std::string> dateToIdMap;
    std::unordered_map<std::string, Transaction> idToTransactionMap;
public:
    InteractionManager(/* args */);
    ~InteractionManager();
    std::string createInteraction(nlohmann::json& data, std::string& date);
};

