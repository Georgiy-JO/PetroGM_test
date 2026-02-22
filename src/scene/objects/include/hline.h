#pragma once

#include "object.h"

namespace scene{
/**
 * @note Судя по тому, что в условии горизонтальная линия задается не только Y-координатой
 * но и парой Х-координат, это вернее назвать отрезком, а не линией. Однако именно такое
 * название было предложено в изначальном документе, по этой причине будем придерживаться
 * таких обозначений.
 */
class HLine: public Object
{
public:
    HLine()=default;
    HLine(double x1, double x2, double y);
    HLine(const HLine& other);
    ~HLine()=default;

    void SetPos(double x1, double x2, double y);
    Vec2 GetBeg() const;
    Vec2 GetEnd() const;
    void Draw(uint8_t* buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels,
                    const Pixel& pixel_size, const Vec2& scene_beg, const Vec2& scene_end) override;

private:
    Vec2 m_beg;
    Vec2 m_end;
};

}   // namespace scene