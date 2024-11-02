#include "derbit_api.h"
#include "http_client/http_client.h"
#include "utils/utils.h"
#include <string>

DerbitApi::DerbitApi(const std::string &client_id, const std::string &secret, const std::string &base_url) : client_id(client_id), secret(secret), base_url(base_url)
{
  HttpClient http_client;

  token = get_token();
}

DerbitApi::~DerbitApi()
{
  std::cout << "DerbitApi Destructor" << std::endl;
}

std::string DerbitApi::get_instrument(std::string &symbol, SCOPE scope)
{
  std::string url = std::format("{}/public/get_instruments?currency={}&kind={}", base_url, symbol, scope_to_string(scope));
  nlohmann::json response = http_client.fetch(url, "");

  return response["result"][0]["instrument_name"];
}

std::string DerbitApi::get_token()
{
  std::string url = std::format("{}/public/auth?client_id={}&client_secret={}&grant_type=client_credentials", base_url, client_id, secret);
  nlohmann::json response = http_client.fetch(url, "");

  return response["result"]["access_token"];
}

nlohmann::json DerbitApi::place_order(const ORDER_TYPE order_type, const ORDER_NAME order_name, const std::string &label, const std::string &instrument, double amount, double price)
{
  std::string url = std::format("{}/private/{}?amount={}&instrument_name={}&label={}&type={}", base_url, order_type_to_string(order_type), amount, instrument, label, order_name_to_string(order_name));

  if (order_name == ORDER_NAME::LIMIT && price != 0)
  {
    url += std::format("&price={}", price);
  }

  nlohmann::json response = http_client.fetch(url, token);

  return response;
}

nlohmann::json DerbitApi::get_order_by_label(const std::string &currency, const std::string &label)
{
  const std::string url = std::format("{}/private/get_open_orders_by_label?currency={}&label={}", base_url, currency, label);

  nlohmann::json response = http_client.fetch(url, token);

  return response["result"][0];
}

void DerbitApi::cancel_order(const std::string &label)
{
  const std::string url = std::format("{}/private/cancel_by_label?label={}", base_url, label);

  http_client.fetch(url, token);
}

void DerbitApi::modify_order(const std::string &label, const std::string &instrument, double amount, double price)
{
  const std::string url = std::format("{}/private/edit_by_label?amount={}&instrument_name={}&price={}&label={}", base_url, amount, instrument, price, label);

  nlohmann::json response = http_client.fetch(url, token);
}

nlohmann::json DerbitApi::get_orderbook(const std::string &instrument)
{
  const std::string url = std::format("{}/public/get_order_book?depth=5&instrument_name={}", base_url, instrument);

  nlohmann::json response = http_client.fetch(url, "");

  return response["result"];
}

nlohmann::json DerbitApi::get_current_positions()
{
  const std::string url = std::format("{}/private/get_positions", base_url);

  nlohmann::json response = http_client.fetch(url, token);

  std::cout << response.dump(4) << "\n";

  return response["result"];
}