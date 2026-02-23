#include "dline.h"
#include <cmath>

namespace scene {
DLine::DLine(double x1, double x2, double y1, double y2) : DLine() { SetPos(x1, x2, y1, y2); }
DLine::DLine(const Vec2& beg, const Vec2& end ) : DLine() { SetPos(beg, end); }
DLine::DLine(const DLine &other) : m_beg(other.m_beg), m_end(other.m_end) {}

void DLine::SetPos(double x1, double x2, double y1, double y2) {
  SetPos(Vec2(x1, y1), Vec2(x2, y2));
}
void DLine::SetPos(const Vec2& beg, const Vec2& end ) {
  if (beg.x > end.x){
    m_beg.x = end.x, m_end.x = beg.x;
    m_beg.y = end.y, m_end.y = beg.y;
  }
  else{
    m_beg.x = beg.x, m_end.x = end.x;
    m_beg.y = beg.y, m_end.y = end.y;
  }
}
Vec2 DLine::GetBeg() const { return m_beg; }
Vec2 DLine::GetEnd() const { return m_end; }
void DLine::Draw(uint8_t *buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels, const Pixel &pixel_size,
                 const Vec2 &scene_beg, const Vec2 &scene_end) {
  if (IsThereParametersIssue(buffer, width_in_pixels, hight_in_pixels, pixel_size) || 
      (m_beg.y < scene_beg.y && m_end.y < scene_beg.y) ||
      (m_beg.y > scene_end.y && m_end.y > scene_end.y) || 
      (m_beg.x < scene_beg.x && m_end.x < scene_beg.x) ||
      (m_beg.x > scene_end.x && m_end.x > scene_end.x))
    return;
  
  unsigned int x1 = AffineTransformationToPixel(m_beg.x, scene_beg.x, pixel_size.GetWidth(), width_in_pixels);
  unsigned int x2 = AffineTransformationToPixel(m_end.x, scene_beg.x, pixel_size.GetWidth(), width_in_pixels);
  unsigned int y1 = AffineTransformationToPixel(m_beg.y, scene_beg.y, pixel_size.GetHight(), hight_in_pixels);  
  unsigned int y2 = AffineTransformationToPixel(m_end.y, scene_beg.y, pixel_size.GetHight(), hight_in_pixels);

  double a_of_y = (static_cast<double>(y2) - y1) / (static_cast<double>(x2) - x1);
  double b_of_y = static_cast<double>(y1) - a_of_y * x1;
  double a_of_x = 1.0f/a_of_y;
  double b_of_x = static_cast<double>(x1) - a_of_x * y1;
  
  if(y2<y1) std::swap(y1, y2);
  
  size_t buffer_pos;
  unsigned int x, y;
  for (y = y1; y <= y2; y++) {
    x = static_cast<unsigned int>(std::round(a_of_x * y + b_of_x));
    buffer_pos = ((hight_in_pixels - y-1) * width_in_pixels + x) * 3;
    (buffer)[buffer_pos] = m_color.blue;
    (buffer)[buffer_pos + 1] = m_color.green;
    (buffer)[buffer_pos + 2] = m_color.red;
  }
  
  for (x = x1; x <= x2; x++) {
    y = static_cast<unsigned int>(std::round(a_of_y * x + b_of_y));
    buffer_pos = ((hight_in_pixels - y-1) * width_in_pixels + x) * 3;   
    (buffer)[buffer_pos] = m_color.blue;
    (buffer)[buffer_pos + 1] = m_color.green;
    (buffer)[buffer_pos + 2] = m_color.red;
  }
}
}  // namespace scene