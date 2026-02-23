#pragma once

namespace scene {

class Pixel {
 public:
  Pixel() : hight(0.0f), width(0.0f) {}
  Pixel(double hight_, double width_) : Pixel() { Set(hight_, width_); }
  Pixel(double val) : Pixel() { Set(val, val); }
  Pixel(const Pixel &other) : hight(other.hight), width(other.width) {}
  ~Pixel() = default;

  void Set(double hight_, double width_) {
    if (hight_ < 0.0f || width_ < 0.0f) throw("Invalid pixel size.");
    hight = hight_;
    width = width_;
  }
  void SetHight(double hight_) { Set(hight_, width); }
  void SetWidth(double width_) { Set(hight, width_); }
  double GetHight() const { return hight; }
  double GetWidth() const { return width; }

  void operator=(const Pixel &other) {
    hight = other.hight;
    width = other.width;
  }

  bool IsZero() const { return hight == 0.0f && width == 0.0f; }

 private:
  double hight;
  double width;
};

}  // namespace scene