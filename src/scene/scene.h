#pragma once
#include <memory>
#include <string>
#include <vector>

#include "object.h"

namespace scene {

class Scene {
 public:
  Scene();
  Scene(const Vec2 &beg, const Vec2 &end, const Color3 &background_color = kDefaultBackgroundColor, unsigned int resolution = kDefaultResolution);
  ~Scene() = default;

  void SetBorders(const Vec2 &beg, const Vec2 &end);
  void AddObject(std::unique_ptr<Object> obj);
  void SetBackgroundColor(const Color3 &color);
  void SetResolution(unsigned int resolution);


  Vec2 GetBeg() const;
  Vec2 GetEnd() const;
  Color3 GetBackgroundColor() const;
  size_t GetObjectsCount() const;
  int GetResolution() const;
  Object *operator()(size_t index);

  void ReplaceObject(size_t index, std::unique_ptr<Object> obj);
  void RemoveObject(size_t index);

  void RenderToBMP(const std::string &result_path) const;

 private:
  constexpr static unsigned int kMaxResolution = 2048;          //check with tests
  constexpr static unsigned int kDefaultResolution = 1024;
  constexpr static unsigned int kMinResolution = 100;           
  constexpr static Color3 kDefaultBackgroundColor = Color3();

  /**
   * @brief Calculates m_pixel_size, m_width_in_pixels, m_height_in_pixels
   */
  void CalculatePixelParameters();

  Vec2 m_beg;  // bottom left conner coordinates
  Vec2 m_end;  // top right conner coordinates
  std::vector<std::unique_ptr<Object>> m_objects;
  Color3 m_background_color;
  unsigned int m_resolution;   // may be changed to differ resolution
  Pixel m_pixel_size;
  unsigned int m_width_in_pixels;
  unsigned int m_height_in_pixels;
};
}  // namespace scene