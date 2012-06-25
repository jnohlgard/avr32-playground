#ifndef FRAMEBUFFER_FRAMEBUFFERCONSOLE_HPP_
#define FRAMEBUFFER_FRAMEBUFFERCONSOLE_HPP_

#include <stddef.h>
#include <stdint.h>
#include "Framebuffer.hpp"
#include "../Stream/BaseOutStream.hpp"
#include "../Stream/formatting.hpp"

class FramebufferConsole : public BaseOutStream
{
    private:
        uint8_t row, col;
        uint8_t monospace;
        Framebuffer* fb;
        bool bound;
        const unsigned char* font_ptr;
        unsigned int font_len;
        uint8_t font_height;
        uint8_t font_stride;
        uint8_t font_base;
        uint8_t font_max;
        const unsigned char* font_data_ptr;

    public:
        explicit FramebufferConsole(Framebuffer* fb_, const uint8_t* font = 0);
        FramebufferConsole();
        FramebufferConsole(const FramebufferConsole& other);
        FramebufferConsole& operator=(const FramebufferConsole& other);
        void bind(Framebuffer* fb_);
        void setFont(const uint8_t* font);
        void setRow(uint8_t row_);
        void setCol(uint8_t col_);
        void setPos(uint8_t x, uint8_t y);
        void setMonospace(uint8_t width);
        void newline();

        BaseOutStream& flush();
        BaseOutStream& put(char_type ch); ///< Put char, advancing column and automatic line wrapping
        BaseOutStream& write(const char_type* s, size_type count);
        uint8_t putChar(char_type ch); ///< Low level put char function without advancing column.
        uint8_t getWidth(char_type ch);

        /// Text using a bitmap font
        void textAt(const uint8_t x0, const uint8_t y0, size_t length, const unsigned char* str);
        void print(const char* str); ///< Print null-terminated string
        void print(uint32_t);
        void print(int32_t);
};

#endif // FRAMEBUFFER_FRAMEBUFFERCONSOLE_HPP_
