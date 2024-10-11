#include "../include/recipe.hpp"
/**
 * @brief Класс, представляющий рецепт.
 */
Recipe::Recipe(const std::string& name,
               const std::vector<std::string>& ingredients)
    : name_(name), ingredients_(ingredients) {}
/**
 * @brief Возвращает название рецепта.
 *
 * @return Название рецепта.
 */
std::string Recipe::GetName() const { return name_; }
/**
 * @brief Возвращает список ингредиентов рецепта.
 *
 * @return Список ингредиентов рецепта.
 */
const std::vector<std::string>& Recipe::GetIngredients() const {
  return ingredients_;
}