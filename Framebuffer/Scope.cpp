#include "Scope.hpp"

Scope::Scope(Framebuffer& fb_,
    const DimensionType x, const DimensionType y,
    const DimensionType w, const DimensionType h) :
    x0(x), y0(y), width(w), height(h),
    fb(fb_),
    current_x(0),
    min_y(0), max_y(0),
    scale_y(height / (max_y - min_y)),
    autoscale(true)
{}

Scope& Scope::put(YValueType y)
{
    static const uint8_t fill[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    if (autoscale && y > max_y)
    {
        ylim(min_y, y);
    }
    else if (autoscale && y < min_y)
    {
        ylim(y, max_y);
    }
    YValueType norm_y = (y - min_y) * scale_y;
    DimensionType fb_y = y0 + height - norm_y - 1; // flip Y-axis
    DimensionType fb_x = x0 + current_x;
    if (fb_y >= y0 + height)
    {
        fb_y = y0 + height - 1;
    }
    else if (fb_y < y0)
    {
        fb_y = y0;
    }
    fb.clearRectangle(fb_x, y0, fb_x, y0 + height - 1);
    fb.pset(fb_x, fb_y);
    ++current_x;
    if (current_x >= width)
    {
        current_x = 0;
    }
    return *this;
}

Scope& Scope::clear()
{
    current_x = 0;
    return *this;
}

Scope& Scope::ylim(YValueType ymin, YValueType ymax)
{
    min_y = ymin;
    max_y = ymax;
    scale_y = height / (max_y - min_y);
    offset_y = -min_y;
    return *this;
}
