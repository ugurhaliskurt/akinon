#include "client/YahooClient.hpp"

#include <iostream>
#include <curl/curl.h>

#include "utilities.hpp"

void YahooClient::setBaseUrl()
{
    baseUrl = "https://query1.finance.yahoo.com/v7/finance/download/{ticker}";
}

std::pair<std::string, double> YahooClient::getExchangeListBasedOnParameter( std::string &symbol )
{
    std::pair<std::string, double> result;
    result.first = symbol;
    try
    {
        setBaseUrl();
        buildUrl(symbol);
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        std::string readBuffer;
        if (curl)
        {
            //fp = fopen(filename.c_str(), "wb");
            curl_easy_setopt(curl, CURLOPT_URL, baseUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);

            /* always cleanup */
            curl_easy_cleanup(curl);
        }
        auto dateValuePair = convertDateValueMap(readBuffer);
        if( dateValuePair.size() > 0 )
            result.second = dateValuePair.begin()->second;

        std::cout << "result.first: " << result.first << "   " << "result.second: " << result.second << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw e;
    }
    return result;
}

void YahooClient::buildUrl(std::string& symbol)
{
    string_replace(baseUrl, "{ticker}", symbol);
}