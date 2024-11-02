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

  std::string instrument = "BTC_EURR";

  std::string client_id_val = "XeTEUwxw";
  std::string client_secret_val = "XMKoU4hTgr2z0SYFpylgo5qqGkwoX-BTEwTnHjBDyac";
  std::string base_url = "https://test.deribit.com/api/v2";
  DerbitApi derbit_api = DerbitApi(client_id_val, client_secret_val, base_url);

  nlohmann::json response = derbit_api.get_current_positions();
  std::cout << "current positions : " << "\n";
  std::cout << response.dump(4) << "\n";

  response = derbit_api.get_orderbook(instrument);
  std::cout << "orderbook: " << "\n";
  std::cout << response.dump(4) << "\n";

  return 0;
}