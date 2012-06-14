#ifndef _ARDUINO3D_MATRIXMATH_HPP_
#define _ARDUINO3D_MATRIXMATH_HPP_

#include "MatrixMxM.hpp"
#include "VectorM.hpp"

namespace A3D
{
template<typename Scalar, DimensionType kDimension>
VectorM<Scalar, kDimension> operator*(
    const MatrixMxM<Scalar, kDimension>& mat,
    const VectorM<Scalar, kDimension>& vect)
{
    VectorM<Scalar, kDimension> res;
    for (DimensionType row = 0; row < kDimension; ++row)
    {
        for (DimensionType i = 0; i < kDimension; ++i)
        {
            res[row] += mat[row*kDimension + i] * vect[i];
        }
    }
    return res;
}

} // namespace A3D
#endif
