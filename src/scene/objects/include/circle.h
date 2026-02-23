#pragma once
#include "object.h"

namespace scene {

class Circle : public Object {
public:
  Circle()=default;
  Circle(const Vec2 &center, double rr);
  Circle(const Circle &other);
  ~Circle() = default;

  void SetCenter(const Vec2 &center);
  void SetR(double rr);
  void SetPos(const Vec2 &center, double rr);
  Vec2 GetCenter() const;
  double GetR() const;
  void Draw(uint8_t *buffer, unsigned int width_in_pixels,
            unsigned int hight_in_pixels, const Pixel &pixel_size,
            const Vec2 &scene_beg, const Vec2 &scene_end) override;

private:
  Vec2 m_center;
  double m_r;
};
} // namespace scene