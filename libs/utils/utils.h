#pragma once
#include <nlohmann/json.hpp>
#include <string>

nlohmann::json get_req(std::string url);