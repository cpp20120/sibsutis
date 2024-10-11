#include "../include/model.hpp"

ModelParams::ModelParams() : step_number(0) {}

/**
 * @brief Constructor for Model
 *
 * @details
 * Constructor for Model
 * @param params The ModelParams object containing the model parameters
 */
Model::Model(const ModelParams &params) : params(params) {
  map.resize(params.map_size.y);
  for (std::size_t i = 0; i < params.map_size.y; i++)
    map[i] = std::vector<int64_t>(params.map_size.x, 0);
}

Model::Model(const Model &other) : params(other.params) {}

std::vector<std::vector<int64_t>> &Model::start() {
  for (std::size_t i = 0; i < params.step_number; i++) step();

  return map;
}

/**
 * @brief step
 * @details
 * Function for one step of the model
 */
void Model::step() {
  // rabbits
  std::vector<std::list<Rabbit>::iterator> new_rabbits;
  for (auto rabbit = params.rabbits.begin(); rabbit != params.rabbits.end();
       rabbit++) {
    rabbit->move(params.map_size);
    if (rabbit->getAge() % 5 == 0) new_rabbits.push_back(rabbit);
    if (rabbit->getAge() == 10) {
      params.rabbits.erase(rabbit);
      if (params.rabbits.size() == 0) break;
    }
  }
  for (auto new_rabbit : new_rabbits)
    params.rabbits.push_back(
        Rabbit({new_rabbit->getPosition(), new_rabbit->getDir(), 0,
                new_rabbit->getSpeed(), new_rabbit->getStability()}));

  // foxes
  std::vector<std::list<Fox>::iterator> new_foxes;
  params.foxes.sort([](const Fox &a, const Fox &b) {
    if (a.getAge() == b.getAge()) return a.getAgeMother() > b.getAgeMother();
    return a.getAge() > b.getAge();
  });
  for (auto fox = params.foxes.begin(); fox != params.foxes.end(); fox++) {
    fox->move(params.map_size);

    if (fox->getAge() == 15) {
      params.foxes.erase(fox);
      if (params.foxes.size() == 0) break;
    }

    for (auto rabbit = params.rabbits.begin(); rabbit != params.rabbits.end();
         rabbit++) {
      if (rabbit->getPosition() == fox->getPosition()) {
        params.rabbits.erase(rabbit);
        fox->eating();
        if (params.rabbits.size() == 0) break;
      }
    }

    if (fox->getEated() >= 2) {
      fox->reproduction();
      new_foxes.push_back(fox);
    }
  }
  for (auto new_fox : new_foxes)
    params.foxes.push_back(Fox({new_fox->getPosition(), new_fox->getDir(), 0,
                                new_fox->getSpeed(), new_fox->getStability()},
                               new_fox->getAge()));

  // map
  for (std::size_t y = 0; y < params.map_size.y; y++) {
    for (std::size_t x = 0; x < params.map_size.x; x++) {
      map[y][x] = 0;
      long long count = 0;
      for (auto rabbit : params.rabbits)
        if (rabbit.getPosition() == Common::Point(x, y)) map[y][x] = ++count;
      count = 0;
      for (auto fox : params.foxes)
        if (fox.getPosition() == Common::Point(x, y)) map[y][x] = --count;
    }
  }
}