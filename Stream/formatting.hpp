#ifndef STREAM_FORMATTING_HPP_
#define STREAM_FORMATTING_HPP_

unsigned int format_ulong(char* str, unsigned long n, unsigned int base = 10, unsigned int max_length = sizeof(unsigned long));
unsigned int format_long(char* str, long signed_n, unsigned int base = 10, unsigned int max_length = sizeof(long));

//~ template<typename T>
//~ void format_uint(unsigned char* str, T n, unsigned int base = 10, unsigned int max_length = sizeof(unsigned long))
//~ {
    //~ format_ulong(str, static_cast<unsigned long>(T), base, max_length);
//~ }
//~
//~ template<typename T>
//~ void format_int(unsigned char* str, T n, unsigned int base = 10, unsigned int max_length = sizeof(unsigned long))
//~ {
    //~ format_long(str, static_cast<long>(T), base, max_length);
//~ }

#endif // STREAM_FORMATTING_HPP_
