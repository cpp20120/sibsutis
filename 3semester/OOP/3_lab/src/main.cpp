#include "../include/model.hpp"
#include "../include/utils/utils.hpp"

auto main() -> int {
  std::print("{}", "Input will get from input.txt\n");
  ModelParams model_params;
  utils::getInput(model_params);
  std::print("{}", "Input was gotten\n");

  Model model(model_params);

  utils::printMap(model.start());
  std::print("{}", "Output printed into output.txt\n");

  return 0;
}