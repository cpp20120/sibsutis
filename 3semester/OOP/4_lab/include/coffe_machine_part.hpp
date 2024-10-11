#ifndef COFFEE_MACHINE_PART_HPP
#define COFFEE_MACHINE_PART_HPP

#include <memory>

#include "./ingridient.hpp"
namespace part {
/**
 * @brief Базовый класс для частей кофемашины.
 */
class CoffeeMachinePart {
 public:
  /**
   * @brief Деструктор.
   */
  virtual ~CoffeeMachinePart() = default;

  /**
   * @brief Обработка ингредиента.
   *
   * @param ingredient Указатель на ингредиент.
   */
  virtual void ProcessIngredient(
      const std::shared_ptr<Ingredient>& ingredient) = 0;
};

/**
 * @brief Класс для моделирования кофемолки.
 */
class Grinder : public CoffeeMachinePart {
 public:
  /**
   * @brief Конструктор.
   */
  Grinder() = default;
  /**
   * @brief Обработка ингредиента.
   *
   * @param ingredient Указатель на ингредиент.
   */
  virtual void ProcessIngredient(
      const std::shared_ptr<Ingredient>& ingredient) override;
};

/**
 * @brief Класс для моделирования группы.
 */
class Group : public CoffeeMachinePart {
 public:
  /**
   * @brief Конструктор.
   */
  Group() = default;
  /**
   * @brief Обработка ингредиента.
   *
   * @param ingredient Указатель на ингредиент.
   */
  virtual void ProcessIngredient(
      const std::shared_ptr<Ingredient>& ingredient) override;
};

/**
 * @brief Класс для моделирования бойлера.
 */
class Boiler : public CoffeeMachinePart {
 public:
  /**
   * @brief Конструктор.
   */
  Boiler() = default;
  /**
   * @brief Обработка ингредиента.
   *
   * @param ingredient Указатель на ингредиент.
   */
  virtual void ProcessIngredient(
      const std::shared_ptr<Ingredient>& ingredient) override;
};

/**
 * @brief Класс для моделирования форсунки.
 */
class Nozzle : public CoffeeMachinePart {
 public:
  /**
   * @brief Конструктор.
   */
  Nozzle() = default;
  /**
   * @brief Обработка ингредиента.
   *
   * @param ingredient Указатель на ингредиент.
   */
  void ProcessIngredient(
      const std::shared_ptr<Ingredient>& ingredient) override;
};
}  // namespace part
#endif  // COFFEE_MACHINE_PART_HPP
