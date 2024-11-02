#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include "derbit_api/derbit_api.h"

std::string scope_to_string(SCOPE scope);
std::string order_type_to_string(ORDER_TYPE order);
std::string order_name_to_string(ORDER_NAME name);
