#include "FramebufferConsole.hpp"
#include <cstring>

/**
 * Font format:
 * parameters followed by data in a uint8 array
 * uint8 common glyph height
 * uint8 bytes per glyph
 * uint8 ascii index of first char
 * uint8 ascii index of last char
 * data:
 *   uint8 this glyph width
 *   uint8[stride-1] pixel data
 */
FramebufferConsole::FramebufferConsole(Framebuffer* fb_, const uint8_t* font) :
    row(0), col(0), monospace(0), fb(fb_), bound(fb != 0)
{
    if (font != 0)
    {
        setFont(font);
    }
    else
    {
        font_ptr = 0;
        font_len = 0;
        font_height = 0;
        font_stride = 0;
        font_base = 0;
        font_max = 0;
        font_data_ptr = 0;
    }
}

FramebufferConsole::FramebufferConsole() :
    row(0), col(0), monospace(0), fb(0), bound(fb != 0),
    font_ptr(0),
    font_len(0),
    font_height(0),
    font_stride(0),
    font_base(0),
    font_max(0),
    font_data_ptr(0)
{
}

FramebufferConsole::FramebufferConsole(const FramebufferConsole& other) :
    row(other.row), col(other.col), monospace(other.monospace), fb(other.fb), bound(fb != 0),
    font_ptr(other.font_ptr),
    font_len(other.font_len),
    font_height(other.font_height),
    font_stride(other.font_stride),
    font_base(other.font_base),
    font_max(other.font_max),
    font_data_ptr(other.font_data_ptr)
{
}

FramebufferConsole& FramebufferConsole::operator=(const FramebufferConsole& other)
{
    row = other.row;
    col = other.col;
    fb  = other.fb;
    bound = (fb != 0);
    monospace = other.monospace;
    font_ptr = other.font_ptr;
    font_len = other.font_len;
    font_height = other.font_height;
    font_stride = other.font_stride;
    font_base = other.font_base;
    font_max = other.font_max;
    font_data_ptr = other.font_data_ptr;
    return *this;
}

void FramebufferConsole::bind(Framebuffer* fb_)
{
    fb = fb_;
    bound = (fb != 0);
}

void FramebufferConsole::setFont(const uint8_t* font)
{
    if (font != 0)
    {
        font_ptr = font;
        font_height = font_ptr[0];
        font_stride = font_ptr[1];
        font_base = font_ptr[2];
        font_max = font_ptr[3];
        font_len = (font_max - font_base) * font_stride;
        font_data_ptr = &font_ptr[4];
    }
}

void FramebufferConsole::setRow(uint8_t row_)
{
    row = row_;
}

void FramebufferConsole::setCol(uint8_t col_)
{
    col = col_;
}

void FramebufferConsole::setMonospace(uint8_t width)
{
    monospace = width;
}

void FramebufferConsole::setPos(uint8_t x, uint8_t y)
{
    col = x;
    row = y;
}

void FramebufferConsole::newline()
{
    col = 0;
    row += font_height;
    if (row + font_height > fb->height)
    {
        //~ fb->vscroll8(font_height/8 + 1);
        //~ fb->blit(0, 0, fb->width, fb->height - font_height, &fb->data[0]);
        memmove(&fb->data[0], &fb->data[fb->width], fb->kSize - fb->width);
        memset(&fb->data[fb->kSize - fb->width], 0, fb->width);
        row -= 8;
    }
    else
    {
    }
}

uint8_t FramebufferConsole::getWidth(char_type ch)
{
    int index = ch - font_base;
    if (index < 0 || index >= font_max)
    {
        return 0;
    }
    uint8_t width = font_data_ptr[index * font_stride];
    return width;
}

uint8_t FramebufferConsole::putChar(char_type ch)
{
    int index = ch - font_base;
    if (index < 0 || index >= font_max)
    {
        return 0;
    }
    uint8_t width = getWidth(ch);
    const uint8_t* glyph = &font_data_ptr[index * font_stride + 1];
    fb->blit(col, row, width, font_height, glyph);
    return width;
}

BaseOutStream& FramebufferConsole::flush()
{
    fb->flush();
    return *this;
}

BaseOutStream& FramebufferConsole::put(char_type ch)
{
    int index = ch - font_base;
    if (index < 0 || index >= font_max)
    {
        return *this;
    }
    uint8_t width = getWidth(ch);
    if (col + width > fb->width)
    {
        newline();
    }
    const uint8_t* glyph = &font_data_ptr[index * font_stride + 1];
    fb->blit(col, row, width, font_height, glyph);

    return *this;
}

BaseOutStream& FramebufferConsole::write(const char_type* str, size_type count)
{
    bool CR_before = false; // workaround to handle all of \r, \r\n and \n as newlines.
    for (unsigned int i = 0; i < count; ++i)
    {
        unsigned char ch = str[i];
        if (ch == '\0')
        {
            break;
        }
        else if (ch == '\r')
        {
            newline();
        }
        else if (ch == '\n')
        {
            if (!CR_before)
            {
                newline();
            }
            CR_before = false;
        }
        else
        {
            CR_before = false;
            uint8_t width = monospace;
            if (width == 0)
            {
                width = getWidth(str[i]);
            }
            if (col + width > fb->width)
            {
                newline();
            }
            putChar(str[i]);
            col += width + 1;
        }
    }
    return *this;
}

/// Draw text using a bitmap font
/**
 * \note this does not respect \0 end of string bytes, for that functionality, use print()
 */
void FramebufferConsole::textAt(const uint8_t x0, const uint8_t y0, size_t length, const unsigned char* str)
{
    setPos(x0, y0);
    for (unsigned int i = 0; i < length; ++i)
    {
        uint8_t width = putChar(str[i]);

        if (monospace == 0)
        {
            col += width + 1;
        }
        else
        {
            col += monospace;
        }
    }
}

void FramebufferConsole::print(const char_type* str)
{
    size_type i = 0;
    while (str[i] != '\0')
    {
        ++i;
    }
    write(str, i);
}

void FramebufferConsole::print(uint32_t num)
{
    char_type str[11];
    format_ulong(&str[0], num, 10, sizeof(str));
    print(str);
}

void FramebufferConsole::print(int32_t num)
{
    char_type str[11];
    format_long(&str[0], num, 10, sizeof(str));
    print(str);
}
