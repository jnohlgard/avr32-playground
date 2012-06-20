#ifndef STREAM_BASEOUTSTREAM_HPP_
#define STREAM_BASEOUTSTREAM_HPP_

#include <stdint.h>

class BaseOutStream
{
    private:

    public:
        typedef unsigned int size_type;
        typedef char char_type;
        virtual BaseOutStream& flush() = 0;
        virtual BaseOutStream& put(char_type ch) = 0;
        virtual BaseOutStream& write(const char_type* s, size_type count) = 0;
};

BaseOutStream& operator<<(BaseOutStream&, uint32_t);
BaseOutStream& operator<<(BaseOutStream&, int32_t);
BaseOutStream& operator<<(BaseOutStream&, uint16_t);
BaseOutStream& operator<<(BaseOutStream&, int16_t);
BaseOutStream& operator<<(BaseOutStream&, char);
BaseOutStream& operator<<(BaseOutStream&, unsigned char);
BaseOutStream& operator<<(BaseOutStream&, const char*);
BaseOutStream& operator<<(BaseOutStream&, const unsigned char*);
#endif // STREAM_BASEOUTSTREAM_HPP_
