#pragma once

#include <print>
#include <string>
/**
 * @file common.hpp
 * @brief Common functions
 */

class Common {
 public:
 /**
  * @brief Point
  *
  * @param x
  * @param y 
  * @return Common::Point
  */
  struct Point {
    std::size_t x, y;

    Point();
    Point(const std::size_t &x, const std::size_t &y);
    Point(const Point &other);

    Point &operator=(const Point &other);
    friend bool operator==(const Point &left, const Point &right);
  };

  static const std::string input_file_name;
  static const std::string output_file_name;
};