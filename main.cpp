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

  std::string client_id_val = "XeTEUwxw";
  std::string client_secret_val = "XMKoU4hTgr2z0SYFpylgo5qqGkwoX-BTEwTnHjBDyac";
  HttpClient httpClient;
  DerbitApi derbit_api(client_id_val, client_secret_val);

  std::string url = fmt::format("https://test.deribit.com/api/v2/public/auth?client_id={}&client_secret={}&grant_type=client_credentials", client_id_val, client_secret_val);

  nlohmann::json response = httpClient.fetchJson(url);

  std::cout << "Response JSON:\n"
            << response.dump(4) << std::endl;

  return 0;
}