#include "derbit_api.h"
#include "http_client/http_client.h"
#include "utils/utils.h"
#include <string>

DerbitApi::DerbitApi(const std::string &apiId, const std::string &apiSecret) : apiKey(apiId), apiSecret(apiSecret)
{
  HttpClient http_client;
  http_client = http_client;
}

DerbitApi::~DerbitApi()
{
  std::cout << "TradingClient Destructor" << std::endl;
}

std::string DerbitApi::get_instrument(std::string &symbol, SCOPE scope)
{
  std::string url = std::format("https://test.deribit.com/api/v2/public/get_instruments?currency={}&kind={}", symbol, scope_to_string(scope));
  nlohmann::json response = http_client.fetch(url, "");

  return response["result"][0]["instrument_name"];
}

std::string DerbitApi::get_token()
{
  std::string url = std::format("https://test.deribit.com/api/v2/public/auth?client_id={}&client_secret={}&grant_type=client_credentials", apiKey, apiSecret);
  nlohmann::json response = http_client.fetch(url, "");

  return response["result"]["access_token"];
}

nlohmann::json DerbitApi::place_order(const ORDER_TYPE order_type, const ORDER_NAME order_name, const std::string &token, const std::string &label, const std::string &instrument, double amount)
{
  const std::string url = std::format("https://test.deribit.com/api/v2/private/{}?amount={}&instrument_name={}&label={}&type={}", order_type_to_string(order_type), amount, instrument, label, order_name_to_string(order_name));

  nlohmann::json response = http_client.fetch(url, token);

  return response;
}

nlohmann::json DerbitApi::get_order_by_label(const std::string &currency, const std::string &label, const std::string &token)
{
  const std::string url = std::format("https://test.deribit.com/api/v2/private/get_open_orders_by_label?currency={}&label={}", currency, label);

  nlohmann::json response = http_client.fetch(url, token);

  return response["result"][0];
}

void DerbitApi::cancel_order(const std::string &label, const std::string &token)
{
  const std::string url = std::format("https://test.deribit.com/api/v2/private/cancel_by_label?label={}", label);

  http_client.fetch(url, token);
}

void DerbitApi::modifyOrder(const std::string &orderId, double newQuantity, double newPrice)
{
  "https://test.deribit.com/api/v2/private/edit_by_label?amount=150&instrument_name=BTC-PERPETUAL&label=i_love_deribit&price=50111";
  std::cout << "Modifying Order ID: " << orderId << std::endl;
  std::cout << "New Quantity: " << newQuantity << ", New Price: " << newPrice << std::endl;
}

void DerbitApi::getOrderBook(const std::string &symbol)
{
  std::cout << "Fetching Order Book for Symbol: " << symbol << std::endl;
}

void DerbitApi::viewCurrentPositions()
{
  std::cout << "Viewing Current Positions" << std::endl;
}