#include "formatting.hpp"
#include <cstring>

unsigned int format_ulong(char* str, unsigned long n, unsigned int base, unsigned int max_length)
{
    char tmp[sizeof(n) + 1];
    int i = sizeof(tmp) - 1;

    // Convert the given number to an ASCII decimal representation.
    tmp[i] = '\0';
    do
    {
        tmp[--i] = '0' + n % base;
        n /= base;
    } while (n);
    strncpy(str, &tmp[i], max_length);
    return sizeof(tmp) - i;
}

unsigned int format_long(char* str, long signed_n, unsigned int base, unsigned int max_length)
{
    char tmp[sizeof(signed_n) + 1];
    int i = sizeof(tmp) - 1;
    unsigned long n = static_cast<unsigned long>(signed_n);
    if (signed_n < 0)
    {
        n = static_cast<unsigned long>(-signed_n);
    }

    // Convert the given number to an ASCII decimal representation.
    tmp[i] = '\0';
    do
    {
        tmp[--i] = '0' + n % base;
        n /= base;
    } while (n);
    if (signed_n < 0)
    {
        tmp[--i] = '-';
    }
    strncpy(str, &tmp[i], max_length);
    return sizeof(tmp) - i;
}

#if 0
/// Source: Arduino-1.0 SDK
unsigned int format_float(char* str, double number, uint8_t digits)
{
    unsigned int n = 0;
    char* tmp[32];

    // Handle negative numbers
    if (number < 0.0)
    {
        tmp[n++] = '-';
        number = -number;
    }

    // Round correctly so that print(1.999, 2) prints as "2.00"
    double rounding = 0.5;
    for (uint8_t i = 0; i < digits; ++i)
    {
        rounding /= 10.0;
    }

    number += rounding;

    // Extract the integer part of the number and print it
    unsigned long int_part = static_cast<unsigned long>(number);
    double remainder = number - static_cast<double>int_part;
    n += format_ulong(&tmp[n], int_part, 10, );

    // Print the decimal point, but only if there are digits beyond
    if (digits > 0) {
        n += print(".");
    }

    // Extract digits from the remainder one at a time
    while (digits-- > 0)
    {
        remainder *= 10.0;
        int toPrint = int(remainder);
        n += print(toPrint);
        remainder -= toPrint;
    }

    return n;
}

unsigned int format_float(char* str, long signed_n, unsigned int base, unsigned int max_length)
{
    char tmp[sizeof(signed_n) + 1];
    int i = sizeof(tmp) - 1;
    unsigned long n = static_cast<unsigned long>(signed_n);
    if (signed_n < 0)
    {
        n = static_cast<unsigned long>(-signed_n);
    }

    // Convert the given number to an ASCII decimal representation.
    tmp[i] = '\0';
    do
    {
        tmp[--i] = '0' + n % base;
        n /= base;
    } while (n);
    if (signed_n < 0)
    {
        tmp[--i] = '-';
    }
    strncpy(str, &tmp[i], max_length);
    return sizeof(tmp) - i;
}
#endif
