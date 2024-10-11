#pragma once

#include "./animal.hpp"
#include "./common.hpp"

#include <list>
#include <vector>
/**
 * @brief Model
 * struct for defining model parameters
 * @details
 * struct for defining model parameters 
 * @param map_size
 * @param step_number
 * @param rabbits
 * @param foxes
*/

struct ModelParams {
  Common::Point map_size;
  std::size_t step_number;

  std::list<Rabbit> rabbits;
  std::list<Fox> foxes;

  ModelParams();
};
/**
 * @brief Model
 * class for defining model 
 * @details
 * class for defining model
 * @param params
 * @return Model
 */
class Model {
  ModelParams params;
  std::vector<std::vector<int64_t>> map;

 public:
  Model(const ModelParams &params);
  Model(const Model &other);

  std::vector<std::vector<int64_t>> &start();
  void step();
};