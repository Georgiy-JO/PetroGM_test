#pragma once 

// #include "point.h"
// #include "hline.h"
// #include "vline.h"
// #include "rect.h"
// #include "circle.h"
#include "object.h"

#include <memory>
#include <vector>
#include <string>


namespace scene{



class Scene{
public:
    Scene();
    Scene(const Vec2& beg, const Vec2& end, const Color3& background_color = kDefaultBackgroundColor);
    ~Scene()=default;

    void SetBorders(const Vec2& beg, const Vec2& end);
    void AddObject(std::unique_ptr<Object> obj);
    void SetBackgroundColor(const Color3& color);

    Vec2 GetBeg() const;
    Vec2 GetEnd() const;
    Color3 GetBackgroundColor() const;
    const Object* GetObject(size_t index) const;
     Object* GetObject(size_t index);
    size_t GetObjectsCount() const;

    void ChangeObject(size_t index, std::unique_ptr<Object> obj);
    void RemoveObject(size_t index);

    void RenderToBMP(const std::string& result_path) const;

private:
    constexpr static unsigned int kMaxSizeInPixels = 1024;       // might be changed
    constexpr static Color3 kDefaultBackgroundColor=Color3();

    /**
     * @brief Calculates m_pixel_size, m_width_in_pixels, m_height_in_pixels
     */
    void CalculatePixelParameters();

    Vec2 m_beg; // bottom left conner coordinates
    Vec2 m_end; // top right conner coordinates
    std::vector<std::unique_ptr<Object>> m_objects;
    Color3 m_background_color;
    Pixel m_pixel_size;
    unsigned int m_width_in_pixels;
    unsigned int m_height_in_pixels;


};
}   // namespace scene