#include "object.h"
#include <cmath>


namespace scene{

    Color3 Object::GetColor() const { return m_color; }
    void Object::SetColor(const Color3 &color) { m_color = color; }

    bool Object::IsThereParametersIssue(uint8_t *buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels,
                              const Pixel &pixel_size) const {
        return pixel_size.IsZero() || buffer == nullptr || width_in_pixels == 0 || hight_in_pixels == 0;
    }
    unsigned int Object::AffineTransformationToPixel(double val, double scene_beg_val, double pixel_size, unsigned int scene_length_pix ){
        double tmp = std::round((val - scene_beg_val) / pixel_size);
        unsigned int pix_val = static_cast<unsigned int>((tmp < 0) ? 0 : tmp);
        pix_val = (pix_val >= scene_length_pix) ? scene_length_pix - 1 : pix_val;
        return pix_val;
    }


}   //namespace scene