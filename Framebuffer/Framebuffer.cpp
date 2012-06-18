#include "Framebuffer.hpp"
#ifndef abs
#define abs(x) ((x)>0?(x):-(x))
#endif

Framebuffer::Framebuffer(FBDimensionType width_, FBDimensionType height_, uint8_t* data_) :
            width(width_),
            height(height_),
            kSize(width * height/8),
            data(data_)
{
}

void Framebuffer::init()
{
}

void Framebuffer::flush()
{
}

void Framebuffer::clear(uint8_t filler)
{
    for (FBLengthType i = 0; i < kSize; ++i)
    {
        data[i] = filler;
    }
}

/// Bresenham's line drawing algorithm
void Framebuffer::line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool color)
{
    int8_t dx = abs(x2 - x1);
    int8_t dy = abs(y2 - y1);
    //~ if (dx == 1 && dy == 1)
    //~ {
        //~ /// \bug ugly hack fix for too small e2 and err variable
        //~ ++dx;
    //~ }

    int8_t sx = 1; // Step direction
    int8_t sy = 1; // Step direction
    if (x1 > x2)
    {
        sx = -1;
    }
    if (y1 > y2)
    {
        sy = -1;
    }

    int16_t err = dx-dy; // Error counter
    uint8_t x = x1;
    uint8_t y = y1;
    uint8_t* pixel = &data[y/8*width + x];
    uint8_t by = y % 8; // sub-byte (bit) position
    uint8_t bitmask = 1<<by;
    //~ Serial.print("x1 = ");
    //~ Serial.print(x1);
    //~ Serial.print(" x2 = ");
    //~ Serial.print(x2);
    //~ Serial.print(" y1 = ");
    //~ Serial.print(y1);
    //~ Serial.print(" y2 = ");
    //~ Serial.println(y2);
    while (x != x2 || y != y2)
    {
        if (/*y < 0 || x < 0 ||*/ y >= height || x >= width)
        {
            // Outside device!
            break;
        }
        //~ Serial.print("x = ");
        //~ Serial.print(x);
        //~ Serial.print(" y = ");
        //~ Serial.print(y);
        pixel = &data[y/8*width + x];
        by = y % 8; // sub-byte (bit) position
        bitmask = 1<<by;
        *pixel |= bitmask;
        int16_t e2 = 2*err;
        //~ Serial.print(" err = ");
        //~ Serial.print(err);
        //~ Serial.print(" e2 = ");
        //~ Serial.println(e2);
        if (e2 > -dy)
        {
            err -= dy;
            x   += sx;
            //~ pixel += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y   += sy;
        }

        //~ uint8_t By = y1/8; // Byte position, 1 byte per 8 Y values
        //~ uint8_t by = y1%8; // sub-byte (bit) position
        //~ uint8_t Bx = x2; // Byte position, 1 byte per 1 X value
                         //~ // No sub-byte position in X
        //~ uint8_t bitmask = 1<<by;
    }
    if (color)
    {
        // inverted
    }
}

void Framebuffer::blit(uint8_t x0, uint8_t y0, const uint8_t buffer_width, const uint8_t buffer_height, const uint8_t* buf)
{
    if (buffer_height == 0 || buffer_width == 0)
    {
        return;
    }
    uint8_t yshifts = y0 % 8; // if y0 is not a multiple of 8 we need to shift the data bytes some bits

    uint8_t ysbound = (buffer_height - 1) / 8 + 1; // calculate source buffer bound
    uint8_t ytbound = (height - 1) / 8 + 1; // calculate framebuffer bound
    uint8_t yt = y0 / 8; // position in framebuffer
    uint8_t ys = 0; // position in source buffer
    while (ys < ysbound && yt < ytbound)
    {
        uint8_t source_mask = 0xFF; // rowmask defines which bit rows are blitted
        if ((ys+1)*8 > buffer_height)
        {
            // partial byte row needs to mask some pixel rows
            source_mask >>= ((ys+1)*8 - buffer_height);
        }
        uint16_t target_mask = ~(source_mask << yshifts);
        uint8_t upper_target_mask = ((target_mask & 0xFF00) >> 8);
        uint8_t lower_target_mask = ((target_mask & 0xFF) >> 0);

        // if the target rectangle is unaligned with the framebuffer's byte rows
        // we will need to split the data somewhere and do two writes to the FB
        uint8_t xt = x0; // position in framebuffer
        uint8_t xs = 0; // position in source buffer
        while (xs < buffer_width && xt < width)
        {
            // source buffer data for upper part of this row
            uint16_t blit_data =
                ((buf[xs + ys * buffer_width] & source_mask) << yshifts);
                //~ ((0xff & source_mask) << yshifts);
            uint8_t upper_byte = ((blit_data & 0xFF00) >> 8);
            uint8_t lower_byte = ((blit_data & 0xFF) >> 0);
            lower_byte |= (data[xt + yt * width] & lower_target_mask); // target buffer data that should be unaffected by the blit
            data[xt + yt * width] = lower_byte;
            //~ data[xt + yt * width] = 0x55;

            if (yt + 1 < ytbound && upper_target_mask != 0xff)
            {
                upper_byte |= (data[xt + (yt+1) * width] & upper_target_mask); // target buffer data that should be unaffected by the blit
                data[xt + (yt+1) * width] = upper_byte;
                //~ data[xt + (yt+1) * width] = 0x00;
            }
            ++xt; // increment target x position
            ++xs; // increment source x position
        }
        ++yt;
        ++ys;
    }
}

void Framebuffer::vscroll8(int8_t offset)
{
    offset_y += offset;
}
