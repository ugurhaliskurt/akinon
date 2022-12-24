#include "Banner.hpp"
#include "Application.hpp"
#include "utilities.hpp"

nlohmann::json Application::handleExchageRate(nlohmann::json& parsed_data)
{
    nlohmann::json myJson;
    std::cout << "**********" << parsed_data.dump() << std::endl;
    try
    {    
        std::string source = parsed_data["source"].get<std::string>();
        std::string targetsStr = parsed_data["targets"].get<std::string>();
        std::vector<std::string> symbols = createSymbols(source, targetsStr);

        std::unordered_map<std::string, double> rates;
        for( auto& symbol : symbols )
            rates.insert( yahooClient.getExchangeListBasedOnParameter(symbol));
        
        for( auto &pair : rates )
        {
            myJson[pair.first] = pair.second;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }
    catch(...)
    {
        std::cout<<"General Error happened" << std::endl;
        throw;
    }
    return myJson;
}

nlohmann::json Application::handleExchage(nlohmann::json& parsed_data)
{
    nlohmann::json myJson;
    try
    {    
        int amount = parsed_data["amount"].get<int>();
        std::string source = parsed_data["source"].get<std::string>();
        std::string targetsStr = parsed_data["targets"].get<std::string>();
        std::vector<std::string> symbols = createSymbols(source, targetsStr);

        std::unordered_map<std::string, double> rates;
        for( auto& symbol : symbols )
            rates.insert( yahooClient.getExchangeListBasedOnParameter(symbol));

        for( auto &pair : rates )
        {
            myJson[pair.first] = amount * pair.second;
        }
        //ToDo
        std::string date = yearMonthDayDateNow();
        auto id = interactionManager.createInteraction(myJson,date);
        myJson["id"] = id;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }
    catch(...)
    {
        std::cout<<"General Error happened" << std::endl;
        throw;
    }
    return myJson;
}

nlohmann::json Application::handleExchageList(nlohmann::json& parsed_data)
{
    nlohmann::json myJsonArray = nlohmann::json::array();
    try
    {
        std::string transactionId = parsed_data["id"].get<std::string>();
        if(transactionId != "")
            return interactionManager.getTransactionById(transactionId).data;

        // search by start date and end date
        std::string startDate = parsed_data["startDate"].get<std::string>();
        std::string endDate = parsed_data["endDate"].get<std::string>();
        auto transactions = interactionManager.getTransactionsByDateFilter(startDate, endDate);


        nlohmann::json myJson;
        for( auto &element : transactions )
        {
            myJson["data"] = element.data;
            myJson["date"] = element.date;
            myJson["id"] = element.id;
            myJsonArray.push_back(myJson);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }
    catch(...)
    {
        std::cout<<"General Error happened" << std::endl;
        throw;
    }

    return myJsonArray;
}


std::vector<std::string> Application::getCurrencies(std::string& targetsStr)
{
    std::vector<std::string> targets;
    std::stringstream ss(targetsStr);
 
    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ',');
        targets.push_back(substr);
    }
    return targets;
}

std::vector<std::string> Application::createSymbols(std::string& source, std::string& targetsStr)
{
    auto targets = getCurrencies(targetsStr);
    for(auto& target : targets )
    {
        target = source+target+std::string("=X");
    }
    return targets;
}