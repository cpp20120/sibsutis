#ifndef COFFEE_MACHINE_HPP
#define COFFEE_MACHINE_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "coffe_machine_part.hpp"
#include "recipe.hpp"

// Class Declaration
class CoffeeMachine {
 public:
  CoffeeMachine();  // Constructor

  void MakeDrink(const std::string& recipeName);  // Make a drink

 private:
  std::shared_ptr<Ingredient> CreateIngredient(
      const std::string& name);  // Create Ingredient

  void LoadRecipes(const std::string& filename);  // Load Recipes

  double CalculatePreparationTime(
      const std::string& recipeName);  // Calculate Preparation Time

  std::vector<std::unique_ptr<part::CoffeeMachinePart>>
      parts_;                              // Parts of the Coffee Machine
  std::map<std::string, Recipe> recipes_;  // Recipes map
};

#endif  // COFFEE_MACHINE_HPP
