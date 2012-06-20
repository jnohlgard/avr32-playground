#include "BaseOutStream.hpp"
#include "formatting.hpp"
#include <cstring>

BaseOutStream& operator<<(BaseOutStream& self, uint32_t n)
{
    BaseOutStream::char_type str[11];
    unsigned int len = format_ulong(&str[0], n, 10, sizeof(str));
    self.write(str, len);

    return self;
}

BaseOutStream& operator<<(BaseOutStream& self, int32_t n)
{
    BaseOutStream::char_type str[11];
    unsigned int len = format_long(&str[0], n, 10, sizeof(str));
    self.write(str, len);

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
    unsigned int len = strlen(s);
    self.write(s, len);
    return self;
}

BaseOutStream& operator<<(BaseOutStream& self, const unsigned char* s)
{
    unsigned int len = strlen((char*) s);
    self.write((char*) s, len);
    return self;
}
