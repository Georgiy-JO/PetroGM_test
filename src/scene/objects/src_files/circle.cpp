#include "circle.h"

#include <cmath>
#include <stdexcept>

#include "vline.h"

namespace scene {

Circle::Circle(const Vec2 &center, double rr) : m_center(center) { SetR(rr); }
Circle::Circle(const Circle &other) : m_center(other.m_center), m_r(other.m_r) {}
void Circle::SetCenter(const Vec2 &center) { m_center = center; }
void Circle::SetR(double rr) {
  if (rr < 0) throw std::runtime_error("Circle Setting Error:Radius can't be negative.");
  m_r = rr;
}
void Circle::SetPos(const Vec2 &center, double rr) {
  SetCenter(center);
  SetR(rr);
}
Vec2 Circle::GetCenter() const { return m_center; }
double Circle::GetR() const { return m_r; }
void Circle::Draw(uint8_t *buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels, const Pixel &pixel_size,
                  const Vec2 &scene_beg, const Vec2 &scene_end) {
  if (IsThereParametersIssue(buffer, width_in_pixels, hight_in_pixels, pixel_size) ||
      (m_center.x + m_r < scene_beg.x) || (m_center.x - m_r > scene_end.x) || (m_center.y + m_r < scene_beg.y) ||
      (m_center.y - m_r > scene_end.y)) {
    return;
  }

  // So any circle can be placed inside a square, lets get that square.
  unsigned int x_min_pix = AffineTransformationToPixel(m_center.x - m_r, scene_beg.x, pixel_size.GetWidth(), width_in_pixels);
  unsigned int x_max_pix = AffineTransformationToPixel(m_center.x + m_r, scene_beg.x, pixel_size.GetWidth(), width_in_pixels);
  unsigned int y_min_pix = AffineTransformationToPixel(m_center.y - m_r, scene_beg.y, pixel_size.GetHight(), hight_in_pixels);
  unsigned int y_max_pix = AffineTransformationToPixel(m_center.y + m_r, scene_beg.y, pixel_size.GetHight(), hight_in_pixels);

  Vec2 center_in_scene_coord(m_center.x - scene_beg.x, m_center.y - scene_beg.y);

  size_t buffer_pos;
  Vec2 half_pixel(pixel_size.GetHight() / 2, pixel_size.GetWidth() / 2);
  Vec2 pixel_center;
  double squared_r = m_r * m_r;
  double squared_pixel_delta;  // squared pixel_center and center delta

  // generally speaking it is not the best realization, but that is the one will will stick to for now.
  for (unsigned int y = y_min_pix; y <= y_max_pix; y++) {
    for (unsigned int x = x_min_pix; x <= x_max_pix; x++) {
      pixel_center.x = static_cast<double>(x) * pixel_size.GetWidth() + half_pixel.x;
      pixel_center.y = static_cast<double>(y) * pixel_size.GetHight() + half_pixel.y;
      squared_pixel_delta = std::pow((pixel_center.x - center_in_scene_coord.x), 2) +
                            std::pow((pixel_center.y - center_in_scene_coord.y), 2);
      if (squared_pixel_delta < squared_r) {
        buffer_pos = ((hight_in_pixels - y-1) * width_in_pixels + x) * 3;
        (buffer)[buffer_pos] = m_color.blue;
        (buffer)[buffer_pos + 1] = m_color.green;
        (buffer)[buffer_pos + 2] = m_color.red;
      }
    }
  }
}
}  // namespace scene