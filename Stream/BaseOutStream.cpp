#include "BaseOutStream.hpp"
#include "formatting.hpp"
#include <cstring>

BaseOutStream& BaseOutStream::print(const char* str)
{
    size_type i = 0;
    while (str[i] != '\0')
    {
        ++i;
    }
    write(str, i);
    return *this;
}

BaseOutStream& BaseOutStream::print(uint32_t n)
{
    BaseOutStream::char_type str[11];
    unsigned int len = format_ulong(&str[0], n, 10, sizeof(str));
    write(str, len);

    return *this;
}

BaseOutStream& BaseOutStream::print(int32_t n)
{
    BaseOutStream::char_type str[11];
    unsigned int len = format_long(&str[0], n, 10, sizeof(str));
    write(str, len);

    return *this;
}


BaseOutStream& operator<<(BaseOutStream& self, uint32_t n)
{
    self.print(n);
    return self;
}

BaseOutStream& operator<<(BaseOutStream& self, int32_t n)
{
    self.print(n);
    return self;
}

BaseOutStream& operator<<(BaseOutStream& self, int16_t n)
{
    return operator<<(self, (int32_t) n);
}

BaseOutStream& operator<<(BaseOutStream& self, uint16_t n)
{
    return operator<<(self, (uint32_t) n);
}

BaseOutStream& operator<<(BaseOutStream& self, char ch)
{
    self.put(ch);
    return self;
}

BaseOutStream& operator<<(BaseOutStream& self, unsigned char ch)
{
    self.put((char) ch);
    return self;
}

BaseOutStream& operator<<(BaseOutStream& self, const char* s)
{
    self.print(s);
    return self;
}

BaseOutStream& operator<<(BaseOutStream& self, const unsigned char* s)
{
    self.print((const char*) s);
    return self;
}
