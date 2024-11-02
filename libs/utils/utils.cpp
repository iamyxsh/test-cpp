#include "utils.h"
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s)
{
  size_t totalSize = size * nmemb;
  s->append((char *)contents, totalSize);
  return totalSize;
}

nlohmann::json get_req(std::string url)
{

  CURL *curl = curl_easy_init();
  nlohmann::json jsonResponse;
  std::string readBuffer;

  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }
    else
    {
      try
      {
        jsonResponse = nlohmann::json::parse(readBuffer);
      }
      catch (const std::exception &e)
      {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
      }
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  return jsonResponse["result"];
}