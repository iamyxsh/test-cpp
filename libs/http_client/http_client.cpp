#include "http_client.h"
#include <iostream>
#include <curl/curl.h>

HttpClient::HttpClient()
{
  initializeCurl();
}

HttpClient::~HttpClient()
{
  cleanupCurl();
}

void HttpClient::initializeCurl()
{
  curl_global_init(CURL_GLOBAL_DEFAULT);
}

void HttpClient::cleanupCurl()
{
  curl_global_cleanup();
}

size_t HttpClient::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *buffer)
{
  std::cout << "WriteCallback function" << std::endl;
  size_t totalSize = size * nmemb;
  buffer->append(static_cast<char *>(contents), totalSize);
  return totalSize;
}

nlohmann::json HttpClient::fetchJson(const std::string &url)
{
  std::cout << "Fetching JSON from URL: " << url << std::endl;
  nlohmann::json jsonResponse;
  CURL *curl = curl_easy_init();

  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    struct curl_slist *headers = nullptr;
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

  return jsonResponse;
}