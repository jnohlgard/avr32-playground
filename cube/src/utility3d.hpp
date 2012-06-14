#ifndef _ARDUINO3D_UTILITY3D_HPP_
#define _ARDUINO3D_UTILITY3D_HPP_

#include "MatrixMxM.hpp"
namespace A3D
{

const float pi = 3.1415926535897932384626433832795028841971693993751058f;
const float two_pi = 6.2831853071795864769252867665590057683943387987502116f;
void Frustum(Matrix4f& matrix, const float left, const float right, const float bottom, const float top, const float near, const float far);
void Ortho(Matrix4f& matrix, const float left, const float right, const float bottom, const float top, const float near, const float far);

void Diagonal(Matrix4f& matrix, const float scale);

inline void Identity(Matrix4f& matrix)
{
    Diagonal(matrix, 1.0f);
}

void RotateXrad(Matrix4f& matrix, const float radians);
void RotateYrad(Matrix4f& matrix, const float radians);
void RotateZrad(Matrix4f& matrix, const float radians);

inline void RotateXdeg(Matrix4f& matrix, const float degrees)
{
    RotateXrad(matrix, degrees * (pi/180.0f));
}

inline void RotateYdeg(Matrix4f& matrix, const float degrees)
{
    RotateYrad(matrix, degrees * (pi/180.0f));
}

inline void RotateZdeg(Matrix4f& matrix, const float degrees)
{
    RotateZrad(matrix, degrees * (pi/180.0f));
}

void Scale(Matrix4f& matrix, const float scale_x, const float scale_y, const float scale_z);

inline void Scale(Matrix4f& matrix, const float scale)
{
    Scale(matrix, scale, scale, scale);
}

void Translate(Matrix4f& matrix, const float dx, const float dy, const float dz);

}
#endif
