#ifndef _ARDUINO3D_VECTORM_HPP_
#define _ARDUINO3D_VECTORM_HPP_

#include "ArrayM.hpp"

namespace A3D
{
template<typename MyScalar, DimensionType kDimension> class MatrixMxM; // forward declaration

/// M vector class
template<typename MyScalar, DimensionType kDimension> class VectorM : public ArrayM<MyScalar,kDimension>
{
    private:
        typedef ArrayM<MyScalar, kDimension> MyArray;
        typedef MatrixMxM<MyScalar, kDimension> MyMatrix;
        typedef VectorM<MyScalar, kDimension> MyVector;

    public:
        VectorM() : MyArray() {}
        VectorM(const MyScalar& val) : MyArray(val) {}
        VectorM(const MyScalar* init) : MyArray(init) {}
        VectorM(const MyVector& other) : MyArray(other) {}

        //~ MyScalar& operator[](const DimensionType pos)
        //~ {
            //~ return this->values[pos];
        //~ }
//~
        //~ MyScalar operator[](const DimensionType pos) const
        //~ {
            //~ return this->values[pos];
        //~ }

    protected:

    private:

};

typedef VectorM<float, 4> Vector4f;
typedef VectorM<float, 3> Vector3f;

} // namespace A3D
#endif
