#pragma once

#include "object.h"

namespace scene{
class Rect: public Object
{
public:
    Rect()=default;
    Rect(const Vec2& beg, const Vec2& end);
    Rect(const Rect& other);
    ~Rect()=default;

    void SetPos(const Vec2& beg, const Vec2& end);
    Vec2 GetBeg() const;
    Vec2 GetEnd() const;
    void Draw(uint8_t* buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels,
                    const Pixel& pixel_size, const Vec2& scene_beg, const Vec2& scene_end) override;
private:
    Vec2 m_beg;
    Vec2 m_end;
};
}   // namespace scene