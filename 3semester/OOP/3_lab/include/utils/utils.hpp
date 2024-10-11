#pragma once
#include "../model.hpp"
#include <vector>
#include <cstdint>
namespace utils {
/**
 * @brief getInput
 * @param model
 * @return void
 */
void getInput(ModelParams &model);
/**
 * @brief printMap
 * @param map
 * @return void
*/
void printMap(const std::vector<std::vector<std::int64_t>> &map);
}