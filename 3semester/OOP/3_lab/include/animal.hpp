#pragma once

#include "./common.hpp"
/**
 * @brief Animal
 *
 * struct with position, direction, age, speed, stability
 */
struct AnimalParams {
  Common::Point position;
  std::size_t dir = 0;
  std::size_t age = 0;
  std::size_t speed = 0;
  std::size_t stability = 0;
};
/**
 * @brief Animal
 *
 * Animal class
 * @details
 * Class with position, direction, age, speed, stability
 */
class Animal {
 protected:
  AnimalParams param;

 public:
  Animal() = default;
  Animal(const AnimalParams &param);

  void move(const Common::Point &map_size);
  virtual void aging() = 0;
  void turn();

  Common::Point getPosition();
  std::size_t getAge() const;
  std::size_t getDir();
  std::size_t getStability();
  std::size_t getSpeed();
};

class Rabbit : public Animal {
 public:
  Rabbit(const AnimalParams &param);

  void aging() override;
};

class Fox : public Animal {
  std::size_t eated;
  std::size_t age_mother;

 public:
  Fox(const AnimalParams &param, std::size_t age_mother);

  void eating();
  void reproduction();

  void aging() override;

  std::size_t getEated();
  std::size_t getAgeMother() const;
};