#include "vline.h"

#include <cmath>

namespace scene {
VLine::VLine(double x, double y1, double y2) : VLine() { SetPos(x, y1, y2); }
VLine::VLine(const VLine &other) : m_beg(other.m_beg), m_end(other.m_end) {}

void VLine::SetPos(double x, double y1, double y2) {
  if (y1 > y2)
    m_beg.y = y2, m_end.y = y1;
  else
    m_beg.y = y1, m_end.y = y2;
  m_beg.x = m_end.x = x;
}
Vec2 VLine::GetBeg() const { return m_beg; }
Vec2 VLine::GetEnd() const { return m_end; }
void VLine::Draw(uint8_t *buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels, const Pixel &pixel_size,
                 const Vec2 &scene_beg, const Vec2 &scene_end) {
  if (IsThereParametersIssue(buffer, width_in_pixels, hight_in_pixels, pixel_size) || m_beg.x < scene_beg.x ||
      m_beg.x > scene_end.x || (m_beg.y < scene_beg.y && m_end.y < scene_beg.y) ||
      (m_beg.y > scene_end.y && m_end.y > scene_end.y))
    return;

  unsigned int x = static_cast<unsigned int>(std::round((m_beg.x - scene_beg.x) / pixel_size.GetWidth()));
  x = (x >= width_in_pixels) ? width_in_pixels - 1 : x;

  double tmp = std::round((m_beg.y - scene_beg.y) / pixel_size.GetHight());
  unsigned int y1 = static_cast<unsigned int>((tmp < 0) ? 0 : tmp);
  y1 = (y1 >= hight_in_pixels) ? hight_in_pixels - 1 : y1;

  tmp = std::round((m_end.y - scene_beg.y) / pixel_size.GetHight());
  unsigned int y2 = static_cast<unsigned int>((tmp < 0) ? 0 : tmp);
  y2 = (y2 >= hight_in_pixels) ? hight_in_pixels - 1 : y2;

  size_t buffer_pos;
  for (unsigned int y = y1; y <= y2; y++) {
    buffer_pos = ((hight_in_pixels - y) * width_in_pixels + x) * 3;
    (buffer)[buffer_pos] = m_color.blue;
    (buffer)[buffer_pos + 1] = m_color.green;
    (buffer)[buffer_pos + 2] = m_color.red;
  }
}

}  // namespace scene