#include <iostream>

#include "../include/coffe_machine.hpp"

/**
 * @brief Точка входа в программу.
 *
 * @return Код завершения программы (0 - успешное завершение).
 */
auto main() -> int {
  CoffeeMachine coffeeMachine;

  coffeeMachine.MakeDrink("Латте");

  return 0;
}
