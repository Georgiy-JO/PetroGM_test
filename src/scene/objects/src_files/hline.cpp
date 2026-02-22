#include "hline.h"
#include <cmath>

namespace scene {
HLine::HLine(double x1, double x2, double y) : HLine() { SetPos(x1, x2, y); }
HLine::HLine(const HLine &other) : m_beg(other.m_beg), m_end(other.m_end) {}

void HLine::SetPos(double x1, double x2, double y) {
  if (x1 > x2)
    m_beg.x = x2, m_end.x = x1;
  else
    m_beg.x = x1, m_end.x = x2;
  m_beg.y = m_end.y = y;
}
Vec2 HLine::GetBeg() const { return m_beg; }
Vec2 HLine::GetEnd() const { return m_end; }
void HLine::Draw(uint8_t *buffer, unsigned int width_in_pixels,
                 unsigned int hight_in_pixels, const Pixel &pixel_size,
                 const Vec2 &scene_beg, const Vec2 &scene_end) {
  if (IsThereParametersIssue(buffer, width_in_pixels, hight_in_pixels,
                             pixel_size) ||
      m_beg.y < scene_beg.y || m_beg.y > scene_end.y ||
      (m_beg.x < scene_beg.x && m_end.x < scene_beg.x) ||
      (m_beg.x > scene_end.x && m_end.x > scene_end.x))
    return;

  unsigned int y = static_cast<unsigned int>(
      std::round((m_beg.y - scene_beg.y) / pixel_size.GetHight()));
  y = (y >= hight_in_pixels) ? hight_in_pixels - 1 : y;

  double tmp = std::round((m_beg.x - scene_beg.x) / pixel_size.GetWidth());
  unsigned int x1 = static_cast<unsigned int>((tmp < 0) ? 0 : tmp);
  x1 = (x1 >= width_in_pixels) ? width_in_pixels - 1 : x1;

  tmp = std::round((m_end.x - scene_beg.x) / pixel_size.GetWidth());
  unsigned int x2 = static_cast<unsigned int>((tmp < 0) ? 0 : tmp);
  x2 = (x2 >= width_in_pixels) ? width_in_pixels - 1 : x2;

  size_t buffer_pos;
  for (unsigned int x = x1; x <= x2; x++) {
    buffer_pos = ((hight_in_pixels - y) * width_in_pixels + x) * 3;
    (buffer)[buffer_pos] = m_color.blue;
    (buffer)[buffer_pos + 1] = m_color.green;
    (buffer)[buffer_pos + 2] = m_color.red;
  }
}
} // namespace scene