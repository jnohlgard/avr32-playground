#ifndef FRAMEBUFFER_FRAMEBUFFERCONSOLE_HPP_
#define FRAMEBUFFER_FRAMEBUFFERCONSOLE_HPP_

#include <stddef.h>
#include <stdint.h>
#include "Framebuffer.hpp"

class FramebufferConsole
{
    private:
        uint8_t row, col;
        uint8_t monospace;
        Framebuffer* fb;
        const unsigned char* font_ptr;
        unsigned int font_len;
        uint8_t font_height;
        uint8_t font_stride;
        uint8_t font_base;
        uint8_t font_max;
        const unsigned char* font_data_ptr;

    public:
        FramebufferConsole(Framebuffer* fb_, const uint8_t* font = 0);
        FramebufferConsole();
        FramebufferConsole(const FramebufferConsole& other);
        FramebufferConsole& operator=(const FramebufferConsole& other);
        void setFont(const uint8_t* font);
        void setRow(uint8_t row_);
        void setCol(uint8_t col_);
        void setPos(uint8_t x, uint8_t y);
        void setMonospace(uint8_t width);
        void newline();

        uint8_t putChar(uint8_t ch);
        uint8_t getWidth(uint8_t ch);
        /// Text using a bitmap font
        void textAt(const uint8_t x0, const uint8_t y0, size_t length, const unsigned char* str);
        void print(size_t length, const unsigned char* str);
        void print(const char* str); ///< Print null-terminated string
};

#endif // FRAMEBUFFER_FRAMEBUFFERCONSOLE_HPP_
