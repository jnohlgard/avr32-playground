#include "Render.hpp"
#include <math.h>

namespace A3D
{

void renderWire(Framebuffer& fb, const uint8_t num_indices, const uint8_t verts_per_face, const uint8_t* indices, const Vector4f* vertices)
{
    const float display_scale_x = static_cast<const float>(fb.width/2);
    const float display_scale_y = static_cast<const float>(fb.height/2);
    const Vector4f* v;
    uint8_t x1, y1, x2, y2;
    v = &vertices[indices[0]];
    x1 = static_cast<uint8_t>(fma((*v)[0], display_scale_x, display_scale_x));
    y1 = static_cast<uint8_t>(fma((*v)[1], display_scale_y, display_scale_y));
    uint8_t i = 1;
    for (uint8_t index = 1; index < num_indices; ++index, ++i)
    {
        v = &vertices[indices[index]];
        // Device transformation
        x2 = static_cast<uint8_t>(fma((*v)[0], display_scale_x, display_scale_x));
        y2 = static_cast<uint8_t>(fma((*v)[1], display_scale_y, display_scale_y));
        fb.line(x1, y1, x2, y2, true);
        x1 = x2;
        y1 = y2;
        if (i == verts_per_face-1)
        {
            // close the loop and skip to next poly
            v = &vertices[indices[index-i]];
            i = 0;
            x2 = static_cast<uint8_t>(fma((*v)[0], display_scale_x, display_scale_x));
            y2 = static_cast<uint8_t>(fma((*v)[1], display_scale_y, display_scale_y));
            fb.line(x1, y1, x2, y2, true);
            ++index;
            if (index < num_indices)
            {
                v = &vertices[indices[index]];
                x1 = static_cast<uint8_t>(fma((*v)[0], display_scale_x, display_scale_x));
                y1 = static_cast<uint8_t>(fma((*v)[1], display_scale_y, display_scale_y));
            }
        }
    }
}

} // namespace A3D
