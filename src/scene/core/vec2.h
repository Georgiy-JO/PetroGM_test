#pragma once

namespace scene {
/**
 * @brief 2D vector.
 * @note Any point in 2D space.
 */
struct Vec2 {
  double x;
  double y;

  constexpr Vec2() : x(0.0f), y(0.0f) {}
  constexpr Vec2(double x_, double y_) : x(x_), y(y_) {}
  constexpr Vec2(double val) : x(val), y(val) {}
  constexpr Vec2(const Vec2 &other) : x(other.x), y(other.y) {}
  ~Vec2() = default;

  void operator=(const Vec2 &other) {
    x = other.x;
    y = other.y;
  }
  bool operator==(const Vec2 &other) const {
    return (x == other.x) && (y == other.y);
  }
  bool operator!=(const Vec2 &other) const { return !(*this == other); }
};

} // namespace scene
