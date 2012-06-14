#include "utility3d.hpp"
#include <cmath>

namespace A3D
{

/// Set up a perspective projection
/**
 *
 */
void Frustum(Matrix4f& matrix, const float left, const float right, const float bottom, const float top, const float near, const float far)
{
    uint8_t i = 0;
    //~ // First row
    //~ matrix[i++] = 2.0f*near/(right-left);
    //~ matrix[i++] = 0.0f;
    //~ matrix[i++] = (right+left)/(right-left);
    //~ matrix[i++] = 0.0f;
    //~ // second row
    //~ matrix[i++] = 0.0f;
    //~ matrix[i++] = 2.0f*near/(top-bottom);
    //~ matrix[i++] = (top+bottom)/(top-bottom);
    //~ matrix[i++] = 0.0f;
    //~ // third row
    //~ matrix[i++] = 0.0f;
    //~ matrix[i++] = 0.0f;
    //~ matrix[i++] = -(far + near)/(far - near);
    //~ matrix[i++] = -2*far*near/(far - near);
    //~ // fourth row
    //~ matrix[i++] = 0.0f;
    //~ matrix[i++] = 0.0f;
    //~ matrix[i++] = -1.0f;
    //~ matrix[i++] = 0.0f;
    // Precalculate some divisions that are used twice
    float tmp_rl = 1.0f / (right - left);
    float tmp_tb = 1.0f / (top - bottom);
    float tmp_nf = 1.0f / (near - far);
    // near is always used 2*near, precalculate
    float tmp_near2 = near * 2.0f;
    // First row
    matrix[i++] = tmp_near2 * tmp_rl;
    matrix[i++] = 0.0f;
    matrix[i++] = (right + left) * tmp_rl;
    matrix[i++] = 0.0f;
    // second row
    matrix[i++] = 0.0f;
    matrix[i++] = tmp_near2 * tmp_tb;
    matrix[i++] = (top + bottom) * tmp_tb;
    matrix[i++] = 0.0f;
    // third row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = (far + near) * tmp_nf;
    matrix[i++] = far * tmp_near2 * tmp_nf;
    // fourth row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = -1.0f;
    matrix[i++] = 0.0f;
}

/// Set up a parallel projection matrix
void Ortho(Matrix4f& matrix, const float left, const float right, const float bottom, const float top, const float near, const float far)
{
    uint8_t i = 0;
    // Precalculate some divisions that are used twice
    float tmp_rl = 1.0f / (right - left);
    float tmp_tb = 1.0f / (top - bottom);
    float tmp_nf = 1.0f / (near - far);
    // First row
    matrix[i++] = 2.0f * tmp_rl;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = -(right + left) * tmp_rl;
    // second row
    matrix[i++] = 0.0f;
    matrix[i++] = 2.0f * tmp_tb;
    matrix[i++] = 0.0f;
    matrix[i++] = -(top + bottom) * tmp_tb;
    // third row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 2.0f * tmp_nf;
    matrix[i++] = (far + near) * tmp_nf;
    // fourth row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 1.0f;
}

void Diagonal(Matrix4f& matrix, const float scale)
{
    uint8_t i = 0;
    // first row
    matrix[i++] = scale;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    // second row
    matrix[i++] = 0.0f;
    matrix[i++] = scale;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    // third row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = scale;
    matrix[i++] = 0.0f;
    // fourth row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = scale;
    //~ for (uint8_t i = 0; i < 16; ++i)
    //~ {
        //~ if (i % 5 == 0)
        //~ {
            //~ // Main diagonal
            //~ matrix[i] = 1.0f;
        //~ }
        //~ else
        //~ {
            //~ matrix[i] = 0.0f;
        //~ }
    //~ }
}

void RotateXrad(Matrix4f& matrix, const float radians)
{
    uint8_t i = 0;
    // first row
    matrix[i++] = 1.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    // second row
    matrix[i++] = 0.0f;
    matrix[i++] = std::cos(radians);
    matrix[i++] = -std::sin(radians);
    matrix[i++] = 0.0f;
    // third row
    matrix[i++] = 0.0f;
    matrix[i++] = std::sin(radians);
    matrix[i++] = std::cos(radians);
    matrix[i++] = 0.0f;
    // fourth row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 1.0f;
}

void RotateYrad(Matrix4f& matrix, const float radians)
{
    uint8_t i = 0;
    // first row
    matrix[i++] = std::cos(radians);
    matrix[i++] = 0.0f;
    matrix[i++] = std::sin(radians);
    matrix[i++] = 0.0f;
    // second row
    matrix[i++] = 0.0f;
    matrix[i++] = 1.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    // third row
    matrix[i++] = -std::sin(radians);
    matrix[i++] = 0.0f;
    matrix[i++] = std::cos(radians);
    matrix[i++] = 0.0f;
    // fourth row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 1.0f;
}

void RotateZrad(Matrix4f& matrix, const float radians)
{
    uint8_t i = 0;
    // first row
    matrix[i++] = std::cos(radians);
    matrix[i++] = -std::sin(radians);
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    // second row
    matrix[i++] = std::sin(radians);
    matrix[i++] = std::cos(radians);
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    // third row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 1.0f;
    matrix[i++] = 0.0f;
    // fourth row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 1.0f;
}

void Scale(Matrix4f& matrix, const float scale_x, const float scale_y, const float scale_z)
{
    uint8_t i = 0;
    // first row
    matrix[i++] = scale_x;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    // second row
    matrix[i++] = 0.0f;
    matrix[i++] = scale_y;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    // third row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = scale_z;
    matrix[i++] = 0.0f;
    // fourth row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 1.0f;
}

void Translate(Matrix4f& matrix, const float dx, const float dy, const float dz)
{
    uint8_t i = 0;
    // first row
    matrix[i++] = 1.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = dx;
    // second row
    matrix[i++] = 0.0f;
    matrix[i++] = 1.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = dy;
    // third row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 1.0f;
    matrix[i++] = dz;
    // fourth row
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 0.0f;
    matrix[i++] = 1.0f;
}


} // namespace A3D
