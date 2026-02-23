#pragma once

#include "color3.h"
#include "pixel.h"
#include "vec2.h"

namespace scene {

class Object {
public:
  Object() = default;
  ~Object() = default;

  /**
   * @brief "Draws" the object into the uint8_t* buffer.
   * @note BMP styled buffer- goes from left to right, from bottom to top.
   * @param buffer - resulting buffer: {pixel_1.blue, pixel_1.green,
   * pixel_1.red, pixel_2.blue, etc};
   * @param pixel_size width and hight of a pixel;
   * @param scene_beg - bottom left conner of the scene;
   * @param scene_end - top right conner of the scene.
   */
  virtual void Draw(uint8_t *buffer, unsigned int width_in_pixels,
                    unsigned int hight_in_pixels, const Pixel &pixel_size,
                    const Vec2 &scene_beg, const Vec2 &scene_end) = 0;
  Color3 GetColor() const { return m_color; }
  void SetColor(const Color3 &color) { m_color = color; }

protected:
  constexpr static Color3 kDefaultColor = Color3(255, 255, 255);
  /**
   * @brief Check if there is an issue with some parameters required by Draw(...).
   */
  bool IsThereParametersIssue(uint8_t *buffer, unsigned int width_in_pixels,
                              unsigned int hight_in_pixels,
                              const Pixel &pixel_size) const {
    return pixel_size.IsZero() || buffer == nullptr || width_in_pixels == 0 ||
           hight_in_pixels == 0;
  }
  Color3 m_color = kDefaultColor;
};

} // namespace scene
