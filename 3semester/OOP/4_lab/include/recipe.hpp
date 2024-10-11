#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <string>
#include <vector>

/**
 * @brief Класс, представляющий рецепт.
 */
class Recipe {
 public:
  /**
   * @brief Конструктор без параметров.
   */
  Recipe() = default;

  /**
   * @brief Конструктор для создания рецепта с именем и списком ингредиентов.
   *
   * @param name Название рецепта.
   * @param ingredients Список ингредиентов рецепта.
   */
  Recipe(const std::string& name, const std::vector<std::string>& ingredients);

  /**
   * @brief Возвращает название рецепта.
   *
   * @return Название рецепта.
   */
  std::string GetName() const;

  /**
   * @brief Возвращает список ингредиентов рецепта.
   *
   * @return Список ингредиентов рецепта.
   */
  const std::vector<std::string>& GetIngredients() const;

 private:
  std::string name_;
  std::vector<std::string> ingredients_;
};

#endif  // RECIPE_HPP
