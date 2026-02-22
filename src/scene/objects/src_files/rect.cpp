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
void Rect::Draw(uint8_t *buffer, unsigned int width_in_pixels,
                unsigned int hight_in_pixels, const Pixel &pixel_size,
                const Vec2 &scene_beg, const Vec2 &scene_end) {
  if (IsThereParametersIssue(buffer, width_in_pixels, hight_in_pixels,
                             pixel_size) ||
      (m_beg.x < scene_beg.x && m_end.x < scene_beg.x) ||
      (m_beg.x > scene_end.x && m_end.x > scene_end.x) ||
      (m_beg.y < scene_beg.y && m_end.y < scene_beg.y) ||
      (m_beg.y > scene_end.y && m_end.y > scene_end.y)) {
    return;
  }

  double tmp = std::round((m_beg.x - scene_beg.x) / pixel_size.GetWidth());
  unsigned int x1 = static_cast<unsigned int>((tmp < 0) ? 0 : tmp);
  x1 = (x1 >= width_in_pixels) ? width_in_pixels - 1 : x1;

  tmp = std::round((m_beg.y - scene_beg.y) / pixel_size.GetHight());
  unsigned int y1 = static_cast<unsigned int>((tmp < 0) ? 0 : tmp);
  y1 = (y1 >= hight_in_pixels) ? hight_in_pixels - 1 : y1;

  tmp = std::round((m_end.x - scene_beg.x) / pixel_size.GetWidth());
  unsigned int x2 = static_cast<unsigned int>((tmp < 0) ? 0 : tmp);
  x2 = (x2 >= width_in_pixels) ? width_in_pixels - 1 : x2;

  tmp = std::round((m_end.y - scene_beg.y) / pixel_size.GetHight());
  unsigned int y2 = static_cast<unsigned int>((tmp < 0) ? 0 : tmp);
  y2 = (y2 >= hight_in_pixels) ? hight_in_pixels - 1 : y2;

  size_t buffer_pos;
  for (unsigned int y = y1; y <= y2; y++) {
    for (unsigned int x = x1; x <= x2; x++) {
      buffer_pos = ((hight_in_pixels - y) * width_in_pixels + x) * 3;
      (buffer)[buffer_pos] = m_color.blue;
      (buffer)[buffer_pos + 1] = m_color.green;
      (buffer)[buffer_pos + 2] = m_color.red;
    }
  }
}
} // namespace scene
