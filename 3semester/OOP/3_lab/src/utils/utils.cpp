#include "../../include/utils/utils.hpp"
#include <fstream>
namespace utils {
/**
    * @brief Reads input from a file and populates a ModelParams object.
    * 
    * The input file contains map size, step number, number of rabbits and foxes,
    * and their respective positions, directions, and stabilities.
    * 
    * @param model The ModelParams object to be populated.
    */
void getInput(ModelParams &model) {
  std::ifstream input_file(Common::input_file_name);

  input_file >> model.map_size.x >> model.map_size.y >> model.step_number;

  std::size_t R, F;
  input_file >> R >> F;
  for (std::size_t i = 0; i < R; i++) {
    AnimalParams param;
    input_file >> param.position.x >> param.position.y >> param.dir >>
        param.stability;
    param.speed = 1;
    model.rabbits.push_back(param);
  }
  for (std::size_t i = 0; i < F; i++) {
    AnimalParams param;
    input_file >> param.position.x >> param.position.y >> param.dir >>
        param.stability;
    param.speed = 2;
    model.foxes.push_back(Fox(param, 0));
  }

  input_file.close();
}
/**
 * @brief Prints a 2D map to a file.
 *
 * This function writes a 2D vector of integers to a file specified by Common::output_file_name.
 * Zeros in the map are represented as asterisks (*) and non-zeros are written as their numeric values.
 * Each row of the map is written to a new line in the file.
 *
 * @param map The 2D vector of integers to be printed.
 */
void printMap(const std::vector<std::vector<std::int64_t>> &map) {
  std::ofstream output_file(Common::output_file_name);

  for (std::size_t i = 0; i < map.size(); i++) {
    std::string line;
    for (std::size_t j = 0; j < map[i].size(); j++) {
      if (map[i][j] == 0)
        line.push_back('*');
      else
        line.append(std::format("{}", map[i][j]));
    }
    line.push_back('\n');
    output_file << line;
  }

  output_file.close();
}
}