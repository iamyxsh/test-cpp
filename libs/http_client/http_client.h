#pragma once

#include <string>
#include <nlohmann/json.hpp>

class HttpClient
{
public:
  HttpClient();
  ~HttpClient();

  nlohmann::json fetchJson(const std::string &url);

private:
  void initializeCurl();
  void performRequest();
  void cleanupCurl();

  static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *buffer);

  std::string readBuffer;
};