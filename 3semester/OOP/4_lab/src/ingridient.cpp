#include "../include/ingridient.hpp"
/**
 * @brief Класс для сухих ингредиентов.
 */
DryIngredient::DryIngredient(const std::string& name, double dissolvingTime)
    : name_(name), dissolvingTime_(dissolvingTime) {}

std::string DryIngredient::GetName() const { return name_; }
double DryIngredient::GetTemperature() const { return 24; }
double DryIngredient::GetHeatingTime() const { return 0; }
double DryIngredient::GetDissolvingTime() const { return dissolvingTime_; }
/**
 * @brief Класс для жидких ингредиентов.
 */
WetIngredient::WetIngredient(const std::string& name, double temperature,
                             double heatingTime)
    : name_(name), temperature_(temperature), heatingTime_(heatingTime) {}

std::string WetIngredient::GetName() const { return name_; }
double WetIngredient::GetTemperature() const { return temperature_; }
double WetIngredient::GetHeatingTime() const { return heatingTime_; }
double WetIngredient::GetDissolvingTime() const { return 0; }

Coffee::Coffee() : DryIngredient("Кофе", 0) {}

double Coffee::GetGrindingTime() const { return 14; }
double Coffee::GetBrewingTime() const { return 19; }
