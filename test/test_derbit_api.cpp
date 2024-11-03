#include <gtest/gtest.h>
#include "derbit_api/derbit_api.h"
#include "utils/utils.h"

std::string client_id_val = "XeTEUwxw";
std::string client_secret_val = "XMKoU4hTgr2z0SYFpylgo5qqGkwoX-BTEwTnHjBDyac";
std::string base_url = "https://test.deribit.com/api/v2";
DerbitApi derbit_api = DerbitApi(client_id_val, client_secret_val, base_url);

auto now = std::chrono::system_clock::now();
auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
std::string label = "order-" + std::to_string(timestamp);

class DerbitApiTest : public ::testing::Test
{
protected:
  void TearDown() override
  {
    derbit_api.cancel_order(label);
  }
};

TEST(DerbitAPITest, SpotPlaceOrder)
{

  std::string symbol = "BTC";
  float amount = 1.0;

  SCOPE scope = SCOPE::SPOT;
  ORDER_TYPE order_type = ORDER_TYPE::SELL;
  ORDER_NAME order_name = ORDER_NAME::MARKET;

  std::string instrument = derbit_api.get_instrument(symbol, scope);

  derbit_api.place_order(order_type, order_name, label, instrument, amount, 0);

  nlohmann::json response = derbit_api.get_order_by_label(symbol, label);

  EXPECT_EQ(response["label"], label);
}

TEST(DerbitAPITest, FuturesPlaceOrder)
{

  std::string symbol = "ETH";
  float amount = 10.0;
  float price = 2000;

  SCOPE scope = SCOPE::FUTURES;
  ORDER_TYPE order_type = ORDER_TYPE::BUY;
  ORDER_NAME order_name = ORDER_NAME::LIMIT;

  std::string instrument = "ETH-8NOV24";

  derbit_api.place_order(order_type, order_name, label, instrument, amount, price);

  nlohmann::json response = derbit_api.get_order_by_label(symbol, label);

  EXPECT_EQ(response["label"], label);
}

TEST(DerbitAPITest, OptionsPlaceOrder)
{
  std::string symbol = "USDC";
  float amount = 100.0;
  float price = 440.0;

  SCOPE scope = SCOPE::OPTIONS;
  ORDER_TYPE order_type = ORDER_TYPE::SELL;
  ORDER_NAME order_name = ORDER_NAME::LIMIT;

  std::string instrument = derbit_api.get_instrument(symbol, scope);

  derbit_api.place_order(order_type, order_name, label, instrument, amount, price);

  nlohmann::json response = derbit_api.get_order_by_label(symbol, label);

  EXPECT_EQ(response["label"], label);
}

TEST(DerbitAPITest, ModifyOrder)
{
  std::string symbol = "BTC";
  std::string label = "order-1234567";
  float amount = 1.0;
  float price = 40.0;

  SCOPE scope = SCOPE::SPOT;
  ORDER_TYPE order_type = ORDER_TYPE::BUY;
  ORDER_NAME order_name = ORDER_NAME::LIMIT;

  std::string instrument = derbit_api.get_instrument(symbol, scope);

  nlohmann::json response = derbit_api.place_order(order_type, order_name, label, instrument, amount, price);
  response = derbit_api.get_order_by_label(symbol, label);

  EXPECT_EQ(response["label"], label);
  EXPECT_EQ(response["amount"], amount);
  EXPECT_EQ(response["price"], price);

  double new_amount = 1.2;
  double new_price = 49.5;

  derbit_api.modify_order(label, instrument, new_amount, new_price);

  response = derbit_api.get_order_by_label(symbol, label);

  EXPECT_EQ(response["label"], label);
  EXPECT_EQ(response["amount"], new_amount);
  EXPECT_EQ(response["price"], new_price);

  derbit_api.cancel_order(label);
}

TEST(DerbitAPITest, CancelOrder)
{
  std::string symbol = "USDC";
  float amount = 100.0;
  float price = 440.0;

  SCOPE scope = SCOPE::OPTIONS;
  ORDER_TYPE order_type = ORDER_TYPE::SELL;
  ORDER_NAME order_name = ORDER_NAME::LIMIT;

  std::string instrument = derbit_api.get_instrument(symbol, scope);

  derbit_api.place_order(order_type, order_name, label, instrument, amount, price);
  derbit_api.cancel_order(label);

  nlohmann::json response = derbit_api.get_order_by_label(symbol, label);

  EXPECT_TRUE(response.is_null());
}

TEST(DerbitAPITest, GetOrderbook)
{
  std::string symbol = "BTC";

  SCOPE scope = SCOPE::SPOT;

  std::string instrument = derbit_api.get_instrument(symbol, scope);

  nlohmann::json response = derbit_api.get_orderbook(instrument);

  EXPECT_TRUE(response["asks"].size() > 0);
  EXPECT_TRUE(response["bids"].size() > 0);
  EXPECT_EQ(response["instrument_name"], instrument);
}
