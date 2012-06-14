#ifndef _ARDUINO3D_RENDER_HPP_
#define _ARDUINO3D_RENDER_HPP_

#include "Framebuffer/Framebuffer.hpp"
#include "VectorM.hpp"
#include <stdint.h>

namespace A3D
{
/// Render wireframe
void renderWire(Framebuffer& fb, const uint8_t num_indices, const uint8_t verts_per_face, const uint8_t* indices, const Vector4f* vertices);

} // namespace A3D
#endif
