#include "../include/coffe_machine.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "../include/coffe_machine_part.hpp"

/**
 * @brief Конструктор кофемашины.
 */
CoffeeMachine::CoffeeMachine() {
  parts_.push_back(std::make_unique<part::Grinder>());
  parts_.push_back(std::make_unique<part::Group>());
  parts_.push_back(std::make_unique<part::Boiler>());
  parts_.push_back(std::make_unique<part::Nozzle>());

  LoadRecipes("recipes.txt");
}

/**
 * @brief Приготовление напитка по рецепту.
 *
 * @param recipeName Название рецепта.
 */
void CoffeeMachine::MakeDrink(const std::string& recipeName) {
  try {
    auto it = recipes_.find(recipeName);
    if (it == recipes_.end()) {
      throw std::runtime_error("Ошибка: рецепт " + recipeName + " не найден");
    }

    std::cout << "Приготовление напитка: " << recipeName << std::endl;
    for (const auto& ingredientName : it->second.GetIngredients()) {
      auto ingredient = CreateIngredient(ingredientName);

      for (const auto& part : parts_) {
        part->ProcessIngredient(ingredient);
      }
    }

    std::cout << "Время приготовления: " << CalculatePreparationTime(recipeName)
              << " секунд" << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }
}

/**
 * @brief Создание ингредиента по имени.
 *
 * @param name Название ингредиента.
 * @return Указатель на созданный ингредиент.
 */
std::shared_ptr<Ingredient> CoffeeMachine::CreateIngredient(
    const std::string& name) {
  if (name == "Кофе") {
    return std::make_shared<Coffee>();
  } else if (name == "Молоко") {
    return std::make_shared<WetIngredient>("Молоко", 65, 10);
  } else if (name == "Сахар") {
    return std::make_shared<DryIngredient>("Сахар", 5);
  } else if (name == "Вода") {
    return std::make_shared<WetIngredient>("Вода", 100, 20);
  } else {
    throw std::runtime_error("Unknown ingredient: " + name);
  }
}

/**
 * @brief Загрузка рецептов из файла.
 *
 * @param filename Имя файла с рецептами.
 */
void CoffeeMachine::LoadRecipes(const std::string& filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      std::stringstream ss(line);
      std::string name;
      std::string ingredient;
      std::vector<std::string> ingredients;
      std::getline(ss, name, ',');
      while (std::getline(ss, ingredient, ',')) {
        ingredients.push_back(ingredient);
      }
      recipes_.emplace(name, Recipe(name, ingredients));
    }
    file.close();
  } else {
    throw std::runtime_error("Ошибка: не удалось открыть файл " + filename);
  }
}

/**
 * @brief Расчет времени приготовления напитка по рецепту.
 *
 * @param recipeName Название рецепта.
 * @return Время приготовления напитка.
 */
double CoffeeMachine::CalculatePreparationTime(const std::string& recipeName) {
  double totalTime = 0;
  auto it = recipes_.find(recipeName);
  if (it != recipes_.end()) {
    for (const auto& ingredientName : it->second.GetIngredients()) {
      auto ingredient = CreateIngredient(ingredientName);
      if (ingredient) {
        if (auto coffee = std::dynamic_pointer_cast<Coffee>(ingredient)) {
          totalTime += coffee->GetGrindingTime();
          totalTime += coffee->GetBrewingTime();
        } else if (auto wetIngredient =
                       std::dynamic_pointer_cast<WetIngredient>(ingredient)) {
          totalTime += wetIngredient->GetHeatingTime();
        } else if (auto dryIngredient =
                       std::dynamic_pointer_cast<DryIngredient>(ingredient)) {
          totalTime += dryIngredient->GetDissolvingTime();
        }
      }
    }
  }
  return totalTime;
}
