#pragma once

#include <string>

class ClientBase
{
private:
protected:
    std::string baseUrl;
public:
    virtual void buildUrl( std::string& symbol ) = 0;
    virtual ~ClientBase() = default;
};