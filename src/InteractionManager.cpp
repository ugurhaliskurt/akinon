#include "InteractionManager.hpp"

#include <utility>

InteractionManager::InteractionManager(/* args */)
{
    
}

InteractionManager::~InteractionManager()
{
}

std::string InteractionManager::genereteIngeractionId()
{
    char c;
    int r;
    std::string id;
    srand (time(NULL));    // initialize the random number generator
    for (int i=0; i<20; i++)
    {    
        r = rand() % 26;   // generate a random number
        c = 'a' + r;            // Convert to a character from a-z
        id.push_back(c);
    }
    return id;
}

std::string InteractionManager::createInteraction(nlohmann::json& data, std::string& date)
{
    Transaction transaction;
    transaction.id = genereteIngeractionId();
    transaction.data = data;
    transaction.date = date;

    idToTransactionMap.insert( std::make_pair( transaction.id, transaction ) );
    dateToIdMap.insert( std::make_pair(transaction.date,transaction.id) );

    return transaction.id;
}