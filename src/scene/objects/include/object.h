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
  virtual void Draw(uint8_t *buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels,
                    const Pixel &pixel_size, const Vec2 &scene_beg, const Vec2 &scene_end) = 0;
  Color3 GetColor() const;
  void SetColor(const Color3 &color);

 protected:
  constexpr static Color3 kDefaultColor = Color3(255, 255, 255);
  /**
   * @brief Check if there is an issue with some parameters required by Draw(...).
   */
  bool IsThereParametersIssue(uint8_t *buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels, const Pixel &pixel_size) const;

  /**
   * @brief Function that transforms selected dimension value into pixel.
   * @param val - value in the usual coordinates (1 dimension: x or y).
   * @param scene_beg_val - scene begining (smallest edge) in the usual coordinates (of the same dimension as val).
   * @param pixel_size - the size (in original coordinates) of the pixel side (same dimension as val).
   * @param scene_length_pix - the length (hight/width - depending of the chosen dimension of val) of the scene in pixels.
   * @return Pixel value in the scene of the val.
   * @note If the val's pixel value will end up smaller than scene begining it will be set to the scene begining.
   * @note If the val's pixel value will end up bigger than scene length it will be set to the last pixel of the scene.
   * @note Keep that in mind before passing data to it (manage the ranges carefully).
   */
  static unsigned int AffineTransformationToPixel(double val, double scene_beg_val, double pixel_size, unsigned int scene_length_pix ) ;

  Color3 m_color = kDefaultColor;
};

}  // namespace scene
