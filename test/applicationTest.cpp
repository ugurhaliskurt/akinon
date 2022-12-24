#include "catch.hpp"
#include "Application.hpp"
#include "utilities.hpp"

TEST_CASE("Application Test Suite", "[Sample]")
{
    Application app;
    std::string date = yearMonthDayDateNow();
    SECTION("handleExchage test")
    {
        nlohmann::json myJson;
        myJson["operation"] = 1;
        myJson["source"] = "TRY";
        myJson["targets"] = "EUR,USD,JPY";
        myJson["amount"] = 10000;
        auto result = app.handleExchage(myJson);
        REQUIRE(app.getInteractionManager().getTransactionsByDateFilter(date,date).size() == 1);
        REQUIRE( result.dump() != "" );
    }

    SECTION("handleExchageList test")
    {
        {
            nlohmann::json myJson;
            myJson["operation"] = 1;
            myJson["source"] = "USD";
            myJson["targets"] = "EUR,TRY,JPY";
            myJson["amount"] = 500;
            auto result = app.handleExchage(myJson);
        }
        nlohmann::json myJson;
        myJson["operation"] = 3;
        myJson["id"] = "";
        myJson["startDate"] = "2022-12-20";
        myJson["endDate"] = date;
        auto result = app.handleExchageList(myJson);
        REQUIRE(app.getInteractionManager().getTransactionsByDateFilter(date,date).size() == 1);
        REQUIRE( result.dump() != "" );
    }
}