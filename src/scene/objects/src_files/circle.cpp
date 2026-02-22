#include "circle.h"
#include <cmath>


namespace scene{
    Circle::Circle(const Vec2& senter, double rr) : m_senter(senter), m_r(rr) {}
    void Circle::Draw(uint8_t* buffer, unsigned int width_in_pixels, unsigned int hight_in_pixels,
            const Pixel& pixel_size, const Vec2& scene_beg, const Vec2& scene_end) override {

        if (IsThereParametersIssue(buffer, width_in_pixels, hight_in_pixels, pixel_size) ||
            m_r < 0) {return;}

        // Since aspect is preserved, pixel_size.width == hight, so uniform scale
        double scale = 1.0 / pixel_size.width;  // Uniform due to aspect preservation

        // Map center and radius to pixels
        int pcx = static_cast<int>((cx - mx) * scale);
        int pcy = static_cast<int>((cy - my) * scale);
        int pr = static_cast<int>(r * scale + 0.5);  // Round radius

        // Clip: rough bounding box check
        if (pcx + pr < 0 || pcx - pr >= static_cast<int>(bw) || 
            pcy + pr < 0 || pcy - pr >= static_cast<int>(bh)) return;

        // Filled circle using scanline (horizontal lines)
        for (int py = std::max(0, pcy - pr); py <= std::min(static_cast<int>(bh - 1), pcy + pr); ++py) {
            // Compute half-width in pixels
            double user_dy = (py - pcy) / scale;
            if (std::abs(user_dy) > r) continue;
            double half_width_user = std::sqrt(r * r - user_dy * user_dy);
            int px_left = static_cast<int>((cx - half_width_user - mx) * scale);
            int px_right = static_cast<int>((cx + half_width_user - mx) * scale);

            // Clip
            px_left = std::max(0, px_left);
            px_right = std::min(static_cast<int>(bw - 1), px_right);

            if (px_left > px_right) continue;

            // Fill horizontal line
            for (int px = px_left; px <= px_right; ++px) {
                SetPixel(buffer, bw, px, py);
            }
        }
    }
}   // namespace scene