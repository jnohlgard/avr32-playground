#include "USARTStream.hpp"
#include <cstring>
extern "C"
{
#include <services/serial/serial.h>
}

USARTStream::USARTStream(volatile platform_usart_t* usart_) :
    usart(usart_), bound(usart != 0)
{
}

USARTStream::USARTStream(const USARTStream& other) :
    usart(other.usart), bound(usart != 0)
{
}

USARTStream& USARTStream::operator=(const USARTStream& other)
{
    usart = other.usart;
    bound = (usart != 0);
    return *this;
}

void USARTStream::bind(volatile platform_usart_t* usart_)
{
    usart = usart_;
    bound = (usart != 0);
}

//~ void USARTStream::setRow(uint8_t row_)
//~ {
    //~ row = row_;
//~ }
//~
//~ void USARTStream::setCol(uint8_t col_)
//~ {
    //~ col = col_;
//~ }
//~
//~ void USARTStream::setMonospace(uint8_t width)
//~ {
    //~ monospace = width;
//~ }
//~
//~ void USARTStream::setPos(uint8_t x, uint8_t y)
//~ {
    //~ col = x;
    //~ row = y;
//~ }

void USARTStream::newline()
{
    usart_serial_putchar(usart, '\r');
    usart_serial_putchar(usart, '\n');
}

BaseOutStream& USARTStream::flush()
{
    return *this;
}

BaseOutStream& USARTStream::put(char_type ch)
{
    usart_serial_putchar(usart, ch);
    return *this;
}

BaseOutStream& USARTStream::write(const char_type* str, size_type count)
{
    usart_serial_write_packet(usart, reinterpret_cast<const uint8_t*>(str), count);
    return *this;
}

BaseOutStream& USARTStream::print(const char_type* str, size_type count)
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
            put(str[i]);
        }
    }
    return *this;
}
