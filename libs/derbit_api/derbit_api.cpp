#include "derbit_api.h"
#include "http_client/http_client.h"

DerbitApi::DerbitApi(const std::string &apiId, const std::string &apiSecret) : apiKey(apiKey), apiSecret(apiSecret)
{
  std::cout << "TradingClient Constructor" << std::endl;
}

DerbitApi::~DerbitApi()
{
  std::cout << "TradingClient Destructor" << std::endl;
}

void DerbitApi::placeOrder(const std::string &symbol, double quantity, double price, const std::string &orderType)
{
  std::cout << "Placing Order:" << std::endl;
  std::cout << "Symbol: " << symbol << ", Quantity: " << quantity << ", Price: " << price << ", Order Type: " << orderType << std::endl;
}

void DerbitApi::cancelOrder(const std::string &orderId)
{
  std::cout << "Canceling Order ID: " << orderId << std::endl;
}

void DerbitApi::modifyOrder(const std::string &orderId, double newQuantity, double newPrice)
{
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