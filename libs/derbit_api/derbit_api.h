#pragma once

#include <string>
#include <iostream>
#include "http_client/http_client.h"

enum SCOPE
{
  FUTURES,
  SPOT,
  OPTIONS
};

enum ORDER_TYPE
{
  BUY,
  SELL
};

enum ORDER_NAME
{
  LIMIT,
  MARKET
};

class DerbitApi
{

public:
  DerbitApi(const std::string &client_id, const std::string &secret, const std::string &base_url);
  ~DerbitApi();

  std::string get_instrument(std::string &symbol, SCOPE scope);

  nlohmann::json place_order(const ORDER_TYPE order_type, const ORDER_NAME order_name, const std::string &label, const std::string &instrument, double amount, double price);

  nlohmann::json get_order_by_label(const std::string &currency, const std::string &label);

  void cancel_order(const std::string &label);

  void modify_order(const std::string &label, const std::string &instrument, double amount, double price);

  nlohmann::json get_orderbook(const std::string &instrument);

  nlohmann::json get_current_positions();

private:
  std::string get_token();

  std::string client_id;
  std::string secret;
  std::string token;
  std::string base_url;

  HttpClient http_client;
};