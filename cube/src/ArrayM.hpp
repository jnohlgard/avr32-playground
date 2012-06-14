#ifndef _ARDUINO3D_ARRAYM_HPP_
#define _ARDUINO3D_ARRAYM_HPP_

#include <stdint.h>

namespace A3D
{
typedef uint8_t DimensionType; // Change this in order to use larger than 256x256 matrices
typedef uint8_t LengthType; // Change this in order to use larger than 16x16 matrices

/// kLength element array
template<typename MyScalar, LengthType kLength> class ArrayM
{
    private:
        typedef ArrayM<MyScalar, kLength> MyArray;

    protected:
        MyScalar values[kLength];

    public:
        ArrayM()
        {
            for (DimensionType i = 0; i < kLength; ++i)
            {
                values[i] = MyScalar(); // Value initialized if MyScalar is a primitive type (int, float etc.)
            }
        }

        ArrayM(const MyScalar& value)
        {
            for (DimensionType i = 0; i < kLength; ++i)
            {
                values[i] = value;
            }
        }

        ArrayM(const MyScalar* init)
        {
            for (DimensionType i = 0; i < kLength; ++i)
            {
                values[i] = init[i];
            }
        }

        ArrayM(const ArrayM& other)
        {
            for (DimensionType i = 0; i < kLength; ++i)
            {
                values[i] = other.values[i];
            }
        }

        MyArray& operator=(const MyArray& other)
        {
            for (DimensionType i = 0; i < kLength; ++i)
            {
                values[i] = other.values[i];
            }
            return *this;
        }

        MyScalar& operator[](const DimensionType pos)
        {
            return values[pos];
        }

        MyScalar operator[](const DimensionType pos) const
        {
            return values[pos];
        }

        /// Component-wise addition assignment
        MyArray& operator+=(const MyArray& other)
        {
            for (DimensionType i = 0; i < kLength; ++i)
            {
                values[i] += other[i];
            }
            return *this;
        }

        /// Component-wise addition assignment
        MyArray& operator-=(const MyArray& other)
        {
            for (DimensionType i = 0; i < kLength; ++i)
            {
                values[i] -= other[i];
            }
            return *this;
        }

        /// Multiplication by scalar
        MyArray& operator*=(const MyScalar& other)
        {
            for (DimensionType i = 0; i < kLength; ++i)
            {
                values[i] *= other;
            }
            return *this;
        }

        /// Division by scalar
        MyArray& operator/=(const MyScalar& other)
        {
            for (DimensionType i = 0; i < kLength; ++i)
            {
                values[i] /= other;
            }
            return *this;
        }

        /// Component-wise addition
        MyArray operator+(const MyArray& other) const
        {
            MyArray res(*this);
            res += other;
            return res;
        }

        /// Component-wise subtraction
        MyArray operator-(const MyArray& other) const
        {
            MyArray res(*this);
            res -= other;
            return res;
        }

        //~ virtual void print(Stream& os)
        //~ {
            //~ for (uint8_t i = 0; i < kLength; ++i)
            //~ {
                //~ os.println((*this)[i]);
            //~ }
        //~ }

    private:
};
} // namespace A3D
#endif
