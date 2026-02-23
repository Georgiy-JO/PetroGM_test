#pragma once

#include "object.h"

namespace scene {
/**
 * @note It would be more accurate to call this class of objects "segment", but due to fact that
 * "VLine" and "DLine" are both named "lines" (not a "segment") we will keep the notation style.
 * @note By the way this new DLine class is created for diagonal lines, but can basically be used
 * for vertical and horizontal lines too. We could replace reference to those an render and delete
 * related files completely (^_^).
 * @attention Begining and end of the line are arranged based on X value (beg.y cna be > end.y).
 */
class DLine : public Object {
 public:
  DLine() = default;
  DLine(double x1, double x2, double y1, double y2);
  DLine(const Vec2& beg, const Vec2& end );
  DLine(const DLine &other);
  ~DLine() = default;

  void SetPos(double x1, double x2, double y1, double y2);
  void SetPos(const Vec2& beg, const Vec2& end );
  Vec2 GetBeg() const;
  Vec2 GetEnd() const;
  void Draw(uint8_t *buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels, const Pixel &pixel_size,
            const Vec2 &scene_beg, const Vec2 &scene_end) override;

 private:
  Vec2 m_beg;
  Vec2 m_end;
};

}  // namespace scene