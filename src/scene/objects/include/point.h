#pragma once

#include "object.h"

namespace scene {

class Point : public Object {
public:
  Point() = default;
  Point(const Vec2 &pos);
  Point(const Point &other);
  ~Point() = default;

  void SetPos(const Vec2 &pos);
  Vec2 GetPos() const;
  void Draw(uint8_t *buffer, unsigned int width_in_pixels,
            unsigned int hight_in_pixels, const Pixel &pixel_size,
            const Vec2 &scene_beg, const Vec2 &scene_end) override;

private:
  Vec2 m_pos;
};

} // namespace scene