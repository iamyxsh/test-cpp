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
  DerbitApi(const std::string &apiId, const std::string &apiSecret);
  ~DerbitApi();

  std::string get_token();

  std::string get_instrument(std::string &symbol, SCOPE scope);

  nlohmann::json place_order(const ORDER_TYPE order_type, const ORDER_NAME order_name, const std::string &token, const std::string &label, const std::string &instrument, double amount, double price);

  nlohmann::json get_order_by_label(const std::string &currency, const std::string &label, const std::string &token);

  void cancel_order(const std::string &label, const std::string &token);

  void modify_order(const std::string &label, const std::string &token, const std::string &instrument, double amount, double price);

  nlohmann::json get_orderbook(const std::string &instrument);

  void viewCurrentPositions();

private:
  std::string apiKey;
  std::string apiSecret;

  HttpClient http_client;
};