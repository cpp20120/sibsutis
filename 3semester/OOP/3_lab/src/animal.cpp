#include "../include/animal.hpp"

Animal::Animal(const AnimalParams &param) : param(param) {}

void Animal::move(const Common::Point &map_size) {
  switch (param.dir) {
    case 0: {
      if (static_cast<int64_t>(param.position.y) -
              static_cast<int64_t>(param.speed) <
          0)
        param.position.y = map_size.y + param.position.y - param.speed;
      else
        param.position.y -= param.speed;
    } break;

    case 1: {
      if (param.position.x + param.speed >= map_size.x)
        param.position.x -= map_size.x - param.speed;
      else
        param.position.x += param.speed;
    } break;

    case 2: {
      if (param.position.y + param.speed >= map_size.y)
        param.position.y -= map_size.y - param.speed;
      else
        param.position.y += param.speed;
    } break;

    case 3: {
      if (static_cast<int64_t>(param.position.x) -
              static_cast<int64_t>(param.speed) <
          0)
        param.position.x = map_size.x + param.position.x - param.speed;
      else
        param.position.x -= param.speed;
    } break;

    default:
      break;
  }
  aging();
  turn();
}

void Animal::aging() { param.age++; }

void Animal::turn() {
  if (param.age % param.stability == 0) param.dir = (param.dir + 1) % 4;
}

Common::Point Animal::getPosition() { return param.position; }

std::size_t Animal::getAge() const { return param.age; }

std::size_t Animal::getDir() { return param.dir; }

std::size_t Animal::getStability() { return param.stability; }

std::size_t Animal::getSpeed() { return param.speed; }

Rabbit::Rabbit(const AnimalParams &param) { this->param = param; }

void Rabbit::aging() { param.age++; }

Fox::Fox(const AnimalParams &param, std::size_t age_mother)
    : eated(0), age_mother(age_mother) {
  this->param = param;
}

void Fox::eating() { eated++; }

void Fox::reproduction() { eated -= 2; }

void Fox::aging() {
  param.age++;
  age_mother++;
}

std::size_t Fox::getEated() { return eated; }

std::size_t Fox::getAgeMother() const { return age_mother; }