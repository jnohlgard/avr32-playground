#ifndef STREAM_USARTSTREAM_HPP_
#define STREAM_USARTSTREAM_HPP_

#include <stdint.h>
#include "BaseOutStream.hpp"
#include "formatting.hpp"
extern "C"
{
#include <drivers/usart/usart.h>
}

class USARTStream : public BaseOutStream
{
    private:
        typedef avr32_usart_t platform_usart_t;
        volatile platform_usart_t* usart;
        bool bound;

    public:
        explicit USARTStream(volatile platform_usart_t* usart_ = 0);
        USARTStream(const USARTStream& other);
        USARTStream& operator=(const USARTStream& other);
        void bind(volatile platform_usart_t* usart_);
        //~ void setRow(uint8_t row_);
        //~ void setCol(uint8_t col_);
        //~ void setPos(uint8_t x, uint8_t y);
        void newline();

        BaseOutStream& flush();
        BaseOutStream& put(char_type ch); ///< Put char, advancing column and automatic line wrapping
        BaseOutStream& write(const char_type* s, size_type count);
        uint8_t putChar(char_type ch); ///< Low level put char function without advancing column.
        uint8_t getWidth(char_type ch);

        BaseOutStream& print(const char* str, size_type count); ///< Print null-terminated string
        BaseOutStream& print(const char* str); ///< Print null-terminated string
        BaseOutStream& print(uint32_t);
        BaseOutStream& print(int32_t);
};

#endif // STREAM_USARTSTREAM_HPP_
