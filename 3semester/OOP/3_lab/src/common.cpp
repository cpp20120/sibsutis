#include "../include/common.hpp"
/**
 * @brief Constructor for Point
 *
 * @details
 * Sets x and y to 0.
 */
Common::Point::Point() : x(0), y(0) {}

Common::Point::Point(const std::size_t &x, const std::size_t &y) : x(x), y(y) {}

Common::Point::Point(const Point &other) : x(other.x), y(other.y) {}
/**
 * @brief Assignment operator for Point
 *
 * @details
 * Sets x and y to other.x and other.y
 * @return Common::Point&
 */
Common::Point &Common::Point::operator=(const Point &other) {
  x = other.x;
  y = other.y;
  return *this;
}
/**
 * @brief Equality operator for Point
 *
 * @details
 * Returns true if x and y are equal
 * @param left
 * @param right
 * @return true
 * @return false
 */
bool operator==(const Common::Point &left, const Common::Point &right) {
  return left.x == right.x && left.y == right.y;
}
/**
 * @brief Name of input file
 *
 * @details
 * Name of input file
 */
const std::string Common::input_file_name = "input.txt";
/** 
 * @brief Name of output file
 *
 * @details
 * Name of output file
 */
const std::string Common::output_file_name = "output.txt";