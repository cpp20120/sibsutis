#ifndef INGREDIENT_HPP
#define INGREDIENT_HPP

#include <string>

/**
 * @brief Базовый класс для ингредиентов.
 */
class Ingredient {
 public:
  /**
   * @brief Деструктор.
   */
  virtual ~Ingredient() = default;

  /**
   * @brief Возвращает название ингредиента.
   *
   * @return Название ингредиента.
   */
  virtual std::string GetName() const = 0;

  /**
   * @brief Возвращает температуру ингредиента.
   *
   * @return Температура ингредиента.
   */
  virtual double GetTemperature() const = 0;

  /**
   * @brief Возвращает время нагрева ингредиента.
   *
   * @return Время нагрева ингредиента.
   */
  virtual double GetHeatingTime() const = 0;

  /**
   * @brief Возвращает время растворения ингредиента.
   *
   * @return Время растворения ингредиента.
   */
  virtual double GetDissolvingTime() const = 0;
};

/**
 * @brief Класс для сухих ингредиентов.
 */
class DryIngredient : public Ingredient {
 public:
  /**
   * @brief Конструктор для создания сухих ингредиентов.
   *
   * @param name Название ингредиента.
   * @param dissolvingTime Время растворения ингредиента.
   */
  DryIngredient(const std::string& name, double dissolvingTime);

  /**
   * @brief Возвращает название ингредиента.
   *
   * @return Название ингредиента.
   */
  std::string GetName() const override;

  /**
   * @brief Возвращает температуру ингредиента.
   *
   * @return Температура ингредиента.
   */
  double GetTemperature() const override;

  /**
   * @brief Возвращает время нагрева ингредиента.
   *
   * @return Время нагрева ингредиента.
   */
  double GetHeatingTime() const override;

  /**
   * @brief Возвращает время растворения ингредиента.
   *
   * @return Время растворения ингредиента.
   */
  double GetDissolvingTime() const override;

 private:
  std::string name_;
  double dissolvingTime_;
};

/**
 * @brief Класс для жидких ингредиентов.
 */
class WetIngredient : public Ingredient {
 public:
  /**
   * @brief Конструктор для создания жидких ингредиентов.
   *
   * @param name Название ингредиента.
   * @param temperature Температура ингредиента.
   * @param heatingTime Время нагрева ингредиента.
   */
  WetIngredient(const std::string& name, double temperature,
                double heatingTime);

  /**
   * @brief Возвращает название ингредиента.
   *
   * @return Название ингредиента.
   */
  std::string GetName() const override;

  /**
   * @brief Возвращает температуру ингредиента.
   *
   * @return Температура ингредиента.
   */
  double GetTemperature() const override;

  /**
   * @brief Возвращает время нагрева ингредиента.
   *
   * @return Время нагрева ингредиента.
   */
  double GetHeatingTime() const override;

  /**
   * @brief Возвращает время растворения ингредиента.
   *
   * @return Время растворения ингредиента.
   */
  double GetDissolvingTime() const override;

 private:
  std::string name_;
  double temperature_;
  double heatingTime_;
};

/**
 * @brief Класс для моделирования кофе.
 */
class Coffee : public DryIngredient {
 public:
  /**
   * @brief Конструктор для создания кофе.
   */
  Coffee();

  /**
   * @brief Возвращает время помола кофе.
   *
   * @return Время помола кофе.
   */
  double GetGrindingTime() const;

  /**
   * @brief Возвращает время заваривания кофе.
   *
   * @return Время заваривания кофе.
   */
  double GetBrewingTime() const;
};

#endif  // INGREDIENT_HPP
