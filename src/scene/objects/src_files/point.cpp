

#include "point.h"
#include <math.h>


namespace scene{
    
    Point::Point(const Vec2& pos): m_pos(pos){}
    Point::Point(const Point& other): m_pos(other.m_pos){}

    void Point::SetPos(const Vec2& pos) {m_pos = pos;}
    Vec2 Point::GetPos() const {return m_pos;}
    void Point::Draw(uint8_t* buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels,const Pixel& pixel_size, const Vec2& scene_beg, const Vec2& scene_end) {
        if(IsThereParametersIssue(buffer, width_in_pixels, hight_in_pixels, pixel_size) || 
            m_pos.x < scene_beg.x || m_pos.x > scene_end.x || 
            m_pos.y < scene_beg.y || m_pos.y > scene_end.y)
                return;
        unsigned int x = static_cast<unsigned int>(std::round((m_pos.x - scene_beg.x)/pixel_size.GetWidth()));
        x=(x>=width_in_pixels)?width_in_pixels-1:x;
        unsigned int y = static_cast<unsigned int>(std::round((m_pos.y - scene_beg.y)/pixel_size.GetHight()));
        y=(y>=hight_in_pixels)?hight_in_pixels-1:y;

        size_t buffer_pos = (y*width_in_pixels+x)*3;
        (buffer)[buffer_pos] = m_color.blue;
        (buffer)[buffer_pos+1] = m_color.green;
        (buffer)[buffer_pos+2] = m_color.red;
    }


}   // namespace scene