#pragma once

#include "object.h"

namespace scene {
/**
 * @note Judging by the fact that in the task-file the horizontal line is specified not only by
 * X-coordinate but also a pair of Y-coordinates, it would be more accurate to call it a segment,
 * not a line. However, "line" is exactly the name proposed in the original document,for this 
 * reason we will stick to such notation.
 */
class VLine : public Object {
 public:
  VLine() = default;
  VLine(double x, double y1, double y2);
  VLine(const VLine &other);
  ~VLine() = default;

  void SetPos(double x, double y1, double y2);
  Vec2 GetBeg() const;
  Vec2 GetEnd() const;
  void Draw(uint8_t *buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels, const Pixel &pixel_size,
            const Vec2 &scene_beg, const Vec2 &scene_end) override;

 private:
  Vec2 m_beg;
  Vec2 m_end;
};

}  // namespace scene