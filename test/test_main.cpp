#include <gtest/gtest.h>
#include "derbit_api/derbit_api.h"
#include "utils/utils.h"

auto now = std::chrono::system_clock::now();
auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
std::string client_id_val = "XeTEUwxw";
std::string client_secret_val = "XMKoU4hTgr2z0SYFpylgo5qqGkwoX-BTEwTnHjBDyac";
DerbitApi derbit_api(client_id_val, client_secret_val);
std::string symbol = "BTC";
float amount = 1.0;
float price = 10.0;
std::string label = "order-" + std::to_string(timestamp);
SCOPE scope = SCOPE::SPOT;
ORDER_TYPE order_type = ORDER_TYPE::SELL;
ORDER_NAME order_name = ORDER_NAME::MARKET;

std::string token = derbit_api.get_token();

// TEST(DerbitAPITest, PlaceOrder)
// {
//   std::string instrument = derbit_api.get_instrument(symbol, scope);

//   derbit_api.place_order(order_type, order_name, token, label, instrument, amount);

//   nlohmann::json response = derbit_api.get_order_by_label(symbol, label, token);

//   EXPECT_EQ(response["label"], label);
// }

// TEST(DerbitAPITest, ModifyOrder)
// {
//   std::string instrument = derbit_api.get_instrument(symbol, scope);
//   order_name = ORDER_NAME::LIMIT;
//   order_type = ORDER_TYPE::BUY;
//   nlohmann::json response = derbit_api.place_order(order_type, order_name, token, label, instrument, amount, price);
//   response = derbit_api.get_order_by_label(symbol, label, token);

//   EXPECT_EQ(response["label"], label);
//   EXPECT_EQ(response["amount"], amount);
//   EXPECT_EQ(response["price"], price);

//   double new_amount = 1.2;
//   double new_price = 9.5;

//   derbit_api.modify_order(label, token, instrument, new_amount, new_price);

//   response = derbit_api.get_order_by_label(symbol, label, token);

//   EXPECT_EQ(response["label"], label);
//   EXPECT_EQ(response["amount"], new_amount);
//   EXPECT_EQ(response["price"], new_price);
// }

// TEST(DerbitAPITest, CancelOrder)
// {
//   derbit_api.cancel_order(label, token);

//   nlohmann::json response = derbit_api.get_order_by_label(symbol, label, token);

//   EXPECT_TRUE(response.is_null());
// }

TEST(DerbitAPITest, GetOrderbook)
{
  std::string instrument = derbit_api.get_instrument(symbol, scope);

  nlohmann::json response = derbit_api.get_orderbook(instrument);

  EXPECT_TRUE(response["asks"].size() > 0);
  EXPECT_TRUE(response["bids"].size() > 0);
  EXPECT_EQ(response["instrument_name"], instrument);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}