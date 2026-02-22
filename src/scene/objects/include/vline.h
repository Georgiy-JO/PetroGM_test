#pragma once

#include "object.h"

namespace scene {
/**
 * @note Судя по тому, что в условии вертикальная линия задается не только
 * X-координатой но и парой Y-координат, это вернее назвать отрезком, а не
 * линией. Однако именно такое название было предложено в изначальном документе,
 * по этой причине будем придерживаться таких обозначений.
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
  void Draw(uint8_t *buffer, unsigned int width_in_pixels,
            unsigned int hight_in_pixels, const Pixel &pixel_size,
            const Vec2 &scene_beg, const Vec2 &scene_end) override;

private:
  Vec2 m_beg;
  Vec2 m_end;
};

} // namespace scene