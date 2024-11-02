#include "utils.h"
#include <iostream>
#include <curl/curl.h>
#include <string>
#include "derbit_api/derbit_api.h"

const std::unordered_map<SCOPE, std::string> ScopeToString = {
    {SCOPE::FUTURES, "future"},
    {SCOPE::SPOT, "spot"},
    {SCOPE::OPTIONS, "option"}};

const std::unordered_map<ORDER_TYPE, std::string> OrderTypeToString = {
    {ORDER_TYPE::BUY, "buy"},
    {ORDER_TYPE::SELL, "sell"}};

const std::unordered_map<ORDER_NAME, std::string> OrderNameToString = {
    {ORDER_NAME::LIMIT, "limit"},
    {ORDER_NAME::MARKET, "market"}};

std::string scope_to_string(SCOPE scope)
{
  return ScopeToString.at(scope);
}

std::string order_type_to_string(ORDER_TYPE type)
{
  return OrderTypeToString.at(type);
}

std::string order_name_to_string(ORDER_NAME name)
{
  return OrderNameToString.at(name);
}