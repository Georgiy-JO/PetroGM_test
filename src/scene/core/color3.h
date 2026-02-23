#pragma once

#include <cstdint>

namespace scene {

/**
 * @brief blue & green & red
 * @note Default color is BLACK.
 */
struct Color3 {
  uint8_t blue;
  uint8_t green;
  uint8_t red;

  constexpr Color3() : blue(0), green(0), red(0) {}
  constexpr Color3(uint8_t blue_, uint8_t green_, uint8_t red_) : blue(blue_), green(green_), red(red_) {}
  constexpr Color3(const Color3 &other) : blue(other.blue), green(other.green), red(other.red) {}
  ~Color3() = default;

  void operator=(const Color3 &other) {
    blue = other.blue;
    green = other.green;
    red = other.red;
  }
};

}  // namespace scene