#pragma once    
#include "object.h"


namespace scene{

class Circle : public Object {
public:
    Circle(const Vec2& senter, double rr);

    void Draw(uint8_t* buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels,
            const Pixel& pixel_size, const Vec2& scene_beg, const Vec2& scene_end) override;
    private:
    Vec2 m_senter;
    double m_r;
};


}       //namespace scene