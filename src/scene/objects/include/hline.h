#pragma once

#include "object.h"

namespace scene {
/**
 * @note Judging by the fact that in the task-file the horizontal line is specified not only by
 * Y-coordinate but also a pair of X-coordinates, it would be more accurate to call it a segment,
 * not a line. However, "line" is exactly the name proposed in the original document,for this 
 * reason we will stick to such notation.
 */
class HLine : public Object {
 public:
  HLine() = default;
  HLine(double x1, double x2, double y);
  HLine(const HLine &other);
  ~HLine() = default;

  void SetPos(double x1, double x2, double y);
  Vec2 GetBeg() const;
  Vec2 GetEnd() const;
  void Draw(uint8_t *buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels, const Pixel &pixel_size,
            const Vec2 &scene_beg, const Vec2 &scene_end) override;

 private:
  Vec2 m_beg;
  Vec2 m_end;
};

}  // namespace scene