#include "rect.h"

#include <cmath>

namespace scene {
Rect::Rect(const Vec2 &beg, const Vec2 &end) : Rect() { SetPos(beg, end); }
Rect::Rect(const Rect &other) : m_beg(other.m_beg), m_end(other.m_end) {}

void Rect::SetPos(const Vec2 &beg, const Vec2 &end) {
  m_beg.x = std::min(beg.x, end.x);
  m_beg.y = std::min(beg.y, end.y);
  m_end.x = std::max(beg.x, end.x);
  m_end.y = std::max(beg.y, end.y);
}
Vec2 Rect::GetBeg() const { return m_beg; }
Vec2 Rect::GetEnd() const { return m_end; }
void Rect::Draw(uint8_t *buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels, const Pixel &pixel_size,
                const Vec2 &scene_beg, const Vec2 &scene_end) {
  if (IsThereParametersIssue(buffer, width_in_pixels, hight_in_pixels, pixel_size) ||
      (m_beg.x < scene_beg.x && m_end.x < scene_beg.x) || (m_beg.x > scene_end.x && m_end.x > scene_end.x) ||
      (m_beg.y < scene_beg.y && m_end.y < scene_beg.y) || (m_beg.y > scene_end.y && m_end.y > scene_end.y)) {
    return;
  }

  unsigned int x1 = AffineTransformationToPixel(m_beg.x, scene_beg.x, pixel_size.GetWidth(), width_in_pixels);
  unsigned int y1 = AffineTransformationToPixel(m_beg.y, scene_beg.y, pixel_size.GetHight(), hight_in_pixels);
  unsigned int x2 = AffineTransformationToPixel(m_end.x, scene_beg.x, pixel_size.GetWidth(), width_in_pixels);
  unsigned int y2 = AffineTransformationToPixel(m_end.y, scene_beg.y, pixel_size.GetHight(), hight_in_pixels);

  size_t buffer_pos;
  for (unsigned int y = y1; y <= y2; y++) {
    for (unsigned int x = x1; x <= x2; x++) {
      buffer_pos = ((hight_in_pixels - y-1) * width_in_pixels + x) * 3;
      (buffer)[buffer_pos] = m_color.blue;
      (buffer)[buffer_pos + 1] = m_color.green;
      (buffer)[buffer_pos + 2] = m_color.red;
    }
  }
}
}  // namespace scene
