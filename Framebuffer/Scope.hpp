#ifndef FRAMEBUFFER_SCOPE_HPP
#define FRAMEBUFFER_SCOPE_HPP
#include <Framebuffer/FramebufferConsole.hpp>

//~ template<typename YT>
class Scope
{
    public:
        typedef float YValueType;
        typedef Framebuffer::FBDimensionType DimensionType;
        DimensionType x0;
        DimensionType y0;
        DimensionType width;
        DimensionType height;
        Framebuffer& fb;
        uint32_t current_x;
        YValueType min_y, max_y;
        YValueType offset_y, scale_y;
        bool autoscale;

        Scope(Framebuffer& fb_,
            const DimensionType x, const DimensionType y,
            const DimensionType w, const DimensionType h);

        Scope& put(YValueType y);
        Scope& clear();
        Scope& ylim(YValueType ymin, YValueType ymax);
};
#endif // FRAMEBUFFER_SCOPE_HPP
