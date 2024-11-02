#include <iostream>
#include "libs/derbit_api/derbit_api.h"
#include "libs/utils/utils.h"
#include "libs/http_client/http_client.h"
#include "libs/derbit_api/derbit_api.h"
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <fmt/core.h>
#include <curl/curl.h>

int main()
{

  auto now = std::chrono::system_clock::now();
  auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

  std::string client_id_val = "XeTEUwxw";
  std::string client_secret_val = "XMKoU4hTgr2z0SYFpylgo5qqGkwoX-BTEwTnHjBDyac";
  DerbitApi derbit_api(client_id_val, client_secret_val);

  std::string token = derbit_api.get_token();

  std::string symbol = "BTC";
  float amount = 1.0;
  std::string label = "order-" + std::to_string(timestamp);
  SCOPE scope = SCOPE::FUTURES;
  ORDER_TYPE order_type = ORDER_TYPE::SELL;
  ORDER_NAME order_name = ORDER_NAME::MARKET;

  std::string instrument = derbit_api.get_instrument(symbol, SCOPE::SPOT);

  nlohmann::json response = derbit_api.place_order(order_type, order_name, token, label, instrument, amount);

  std::cout << "Response JSON:\n"
            << response.dump(4) << std::endl;

  return 0;
}