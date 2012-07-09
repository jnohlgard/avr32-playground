#ifndef FRAMEBUFFER_FRAMEBUFFER_HPP_
#define FRAMEBUFFER_FRAMEBUFFER_HPP_

#include <stdint.h>

/// 1 bit per pixel framebuffer
class Framebuffer
{
    public:
        typedef uint8_t FBDimensionType;
        typedef uint16_t FBLengthType;

        const FBDimensionType width;
        const FBDimensionType height;
        const FBLengthType kSize;
        FBDimensionType offset_y;
        //~ FBDimensionType offset_x;

    public:
        Framebuffer(FBDimensionType width_, FBDimensionType height_, uint8_t* data_);

        virtual void init();

        virtual void flush();

        virtual void clear(uint8_t filler = 0x0);

        virtual void fillRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
        virtual void clearRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
        virtual void pset(uint8_t x, uint8_t y);
        virtual void pclr(uint8_t x, uint8_t y);

        /// Bresenham's line drawing algorithm
        virtual void line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool color);

        /// copy a block into framebuffer at arbitrary non divide-by-8 y position
        virtual void blit(uint8_t x0, uint8_t y0, const uint8_t buffer_width, const uint8_t buffer_height, const uint8_t* buf);

        /// Vertical scroll by a multiple of 8
        virtual void vscroll8(int8_t offset);

        uint8_t* data;
};
#endif
