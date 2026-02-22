
#include "scene.h"
#include "libbitmap.h"
#include <cmath>

namespace scene {
Scene::Scene()
    : m_beg(0.0f, 0.0f), m_end(0.0f, 0.0f), m_objects(),
      m_background_color(kDefaultBackgroundColor) {
  CalculatePixelParameters();
}
Scene::Scene(const Vec2 &beg, const Vec2 &end, const Color3 &background_color)
    : m_beg(beg), m_end(end), m_objects(),
      m_background_color(background_color) {
  CalculatePixelParameters();
}

void Scene::SetBorders(const Vec2 &beg, const Vec2 &end) {
  m_beg = beg;
  m_end = end;
  CalculatePixelParameters();
}
void Scene::AddObject(std::unique_ptr<Object> obj) {
  m_objects.push_back(std::move(obj));
}
void Scene::SetBackgroundColor(const Color3 &color) {
  m_background_color = color;
}

Vec2 Scene::GetBeg() const { return m_beg; }
Vec2 Scene::GetEnd() const { return m_end; }
Color3 Scene::GetBackgroundColor() const { return m_background_color; }
const Object *Scene::GetObject(size_t index) const {
  if (index >= GetObjectsCount())
    throw std::runtime_error("Index out of range");
  return m_objects[index].get();
}
Object *Scene::GetObject(size_t index) {
  if (index >= GetObjectsCount())
    throw std::runtime_error("Index out of range");
  return m_objects[index].get();
}
size_t Scene::GetObjectsCount() const { return m_objects.size(); }

void Scene::ChangeObject(size_t index, std::unique_ptr<Object> obj) {
  if (index < GetObjectsCount())
    m_objects[index] = std::move(obj);
  else
    throw std::runtime_error("Index out of range");
}
void Scene::RemoveObject(size_t index) {
  if (index < GetObjectsCount())
    m_objects.erase(m_objects.begin() + index);
  else
    throw std::runtime_error("Index out of range");
}

void Scene::RenderToBMP(const std::string &result_path) const {
  if (m_pixel_size.IsZero())
    throw std::runtime_error("Invalid borders: There is no scene to draw.");

  size_t buffer_size =
      static_cast<size_t>(m_height_in_pixels) * m_width_in_pixels * 3;
  // BMP styled buffer - goes from left to right, from bottom to top.
  Bitmap bmp = Bitmap();
  bmp.m_width = m_width_in_pixels;
  bmp.m_height = m_height_in_pixels;
  bmp.m_buffer = new uint8_t[buffer_size];

  for (size_t i = 0; i < buffer_size; i += 3) {
    (bmp.m_buffer)[i] = m_background_color.blue;
    (bmp.m_buffer)[i + 1] = m_background_color.green;
    (bmp.m_buffer)[i + 2] = m_background_color.red;
  }

  for (auto &obj : m_objects) {
    obj->Draw(bmp.m_buffer, m_width_in_pixels, m_height_in_pixels, m_pixel_size,
              m_beg, m_end);
  }

  bmp.save(result_path.c_str());
  bmp.clear();
}

void Scene::CalculatePixelParameters() {

  if (m_end.x == m_beg.x || m_end.y == m_beg.y) {
    m_pixel_size = Pixel();
    m_width_in_pixels = 0;
    m_height_in_pixels = 0;
    return;
  }
  if (m_beg.x > m_end.x)
    std::swap(m_beg.x, m_end.x);
  if (m_beg.y > m_end.y)
    std::swap(m_beg.y, m_end.y);

  double width = m_end.x - m_beg.x;
  double height = m_end.y - m_beg.y;

  double aspect = width / height;

  if (aspect >= 1) {
    m_pixel_size.SetWidth(width / kMaxSizeInPixels);
    m_width_in_pixels = kMaxSizeInPixels;
    m_height_in_pixels = static_cast<unsigned int>(
        std::round(static_cast<double>(kMaxSizeInPixels) / aspect));
    m_height_in_pixels = std::max(1u, m_height_in_pixels);
    m_pixel_size.SetHight(height / m_height_in_pixels);
  } else {
    m_pixel_size.SetHight(height / kMaxSizeInPixels);
    m_height_in_pixels = kMaxSizeInPixels;
    m_width_in_pixels = static_cast<unsigned int>(
        std::round(static_cast<double>(kMaxSizeInPixels) * aspect));
    m_width_in_pixels = std::max(1u, m_width_in_pixels);
    m_pixel_size.SetWidth(width / m_width_in_pixels);
  }
}

} // namespace scene