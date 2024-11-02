#pragma once

#include <string>
#include <iostream>

class DerbitApi
{
public:
  DerbitApi(const std::string &apiId, const std::string &apiSecret);
  ~DerbitApi();

  void placeOrder(const std::string &symbol, double quantity, double price, const std::string &orderType);

  void cancelOrder(const std::string &orderId);

  void modifyOrder(const std::string &orderId, double newQuantity, double newPrice);

  void getOrderBook(const std::string &symbol);

  void viewCurrentPositions();

private:
  std::string apiKey;
  std::string apiSecret;
};