#ifndef _ARDUINO3D_H_
#define _ARDUINO3D_H_

extern "C" {
#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
}
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "ArrayM.hpp"
#include "MatrixMxM.hpp"
#include "VectorM.hpp"
#include "matrixmath.hpp"
#include "KS0108.hpp"
#include "utility3d.hpp"
#include "Render.hpp"


#endif
