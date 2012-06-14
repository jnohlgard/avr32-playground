#include "ArrayM.hpp"
#include "MatrixMxM.hpp"
#include "VectorM.hpp"
#include "matrixmath.hpp"
#include "Framebuffer/SSD1306.hpp"
#include "utility3d.hpp"
#include "Render.hpp"
#include <cmath>
#include "board.h"
#include "millis.h"
#include "Framebuffer/fonts/tom_thumb.h"
#include <stdio.h>
#include <drivers/cpu/cycle_counter/cycle_counter.h>
#include <services/clock/sysclk.h>

extern "C" {
int _isatty(int file) {
    return 1;
}
}

using A3D::Matrix4f;
using A3D::Vector4f;
typedef SSD1306Framebuffer FBDev;

Matrix4f identity;
Matrix4f ProjectionMatrix;
Matrix4f ModelWorldMatrix;
Matrix4f WorldViewMatrix;
Matrix4f RotationMatrix;
Matrix4f RotationOffsetMatrix;
Matrix4f ScaleMatrix;
Matrix4f MoveMatrix;
Matrix4f RotationXMatrix;
Matrix4f RotationYMatrix;
Matrix4f RotationZMatrix;

Vector4f cube_vertices[8];
uint8_t cube_indices[24];
static const uint8_t num_cubes = 5;

FBDev fb(128, 64);

void initCube(void)
{
    int i=0;
    for (int z = -1; z < 2; z += 2)
    {
        for (int y = -1; y < 2; y += 2)
        {
            for (int x = -1; x < 2; x += 2)
            {
                cube_vertices[i][0] = static_cast<float>(x);
                cube_vertices[i][1] = static_cast<float>(y);
                cube_vertices[i][2] = static_cast<float>(z);
                cube_vertices[i][3] = 1.0f; // homogenous coordinate
                ++i;
            }
        }
    }
    i = 0;
    // -z
    cube_indices[i++] = 0;
    cube_indices[i++] = 2;
    cube_indices[i++] = 3;
    cube_indices[i++] = 1;
    // +z
    cube_indices[i++] = 4;
    cube_indices[i++] = 5;
    cube_indices[i++] = 7;
    cube_indices[i++] = 6;
    // -y
    cube_indices[i++] = 0;
    cube_indices[i++] = 1;
    cube_indices[i++] = 5;
    cube_indices[i++] = 4;
    // +y
    cube_indices[i++] = 2;
    cube_indices[i++] = 6;
    cube_indices[i++] = 7;
    cube_indices[i++] = 3;
    // -x
    cube_indices[i++] = 0;
    cube_indices[i++] = 4;
    cube_indices[i++] = 6;
    cube_indices[i++] = 2;
    // +x
    cube_indices[i++] = 1;
    cube_indices[i++] = 3;
    cube_indices[i++] = 7;
    cube_indices[i++] = 5;
}

void initModelView(void)
{
    A3D::Identity(ModelWorldMatrix);
    A3D::Translate(WorldViewMatrix, 0.0f, 0.0f, -6.0f); // move cube away from camera
    A3D::Identity(ScaleMatrix);
    A3D::Translate(MoveMatrix, 0.0f, 0.0f, -3.0f); // move cube away from camera
}

void initRotationStep(void)
{
    static const float xstep = 1.0f/17.0f;
    static const float ystep = 1.0f/61.0f;
    static const float zstep = 1.0f/37.0f;
    static const float rotoffset = A3D::two_pi/static_cast<float>(num_cubes);

    A3D::RotateXrad(RotationXMatrix, xstep);
    A3D::RotateYrad(RotationYMatrix, ystep);
    A3D::RotateZrad(RotationZMatrix, zstep);
    A3D::RotateYrad(RotationOffsetMatrix, rotoffset);
    RotationMatrix = RotationXMatrix * RotationYMatrix * RotationZMatrix;

    //~ Serial.println("RotationX:");
    //~ RotationXMatrix.print(Serial);
    //~ Serial.println("RotationY:");
    //~ RotationYMatrix.print(Serial);
    //~ Serial.println("RotationZ:");
    //~ RotationZMatrix.print(Serial);
    //~ Serial.println("RotationOffset:");
    //~ RotationOffsetMatrix.print(Serial);
    //~ delay(1000);
    //~ Serial.println("Total Rotation:");
    //~ RotationMatrix.print(Serial);
    //~ delay(1000);
}

void animateCube(void)
{
    ModelWorldMatrix *= RotationMatrix;
    ScaleMatrix[0] = ScaleMatrix[5] = ScaleMatrix[10] = (2.0 + std::sin(millis()/1000.0f)) * 0.3;

    MoveMatrix = RotationYMatrix * MoveMatrix;
}

void drawCube(uint8_t index)
{
    // Calculate transform: Model to world to view to projection to device
    Matrix4f SystemMatrix = MoveMatrix;
    for (uint8_t i = 0; i < index; ++i)
    {
        // Offset each cube from the others
        SystemMatrix = RotationOffsetMatrix * SystemMatrix;
    }
    Matrix4f total_transform = ProjectionMatrix * WorldViewMatrix * SystemMatrix * ScaleMatrix * ModelWorldMatrix;
    //~ Matrix4f total_transform = ProjectionMatrix * WorldViewMatrix * ModelWorldMatrix;
    // Draw quads
    Vector4f transformed_verts[8];
    for (uint8_t i = 0; i < 8; ++i)
    {
        transformed_verts[i] = total_transform * cube_vertices[i];
        transformed_verts[i] /= transformed_verts[i][3]; // Perspective divide
        //~ Serial.print("Vertex ");
        //~ Serial.println(i);
        //~ transformed_verts[i].print(Serial);
    }
    A3D::renderWire(fb, 24, 4, &cube_indices[0], &transformed_verts[0]);
}

void setup(void)
{
    //~ Serial.begin(115200);
    //~ hwinit();
    sysclk_init();
    fb.init();
    fb.clear();
    fb.flush();
    initCube();
    initModelView();
    static const float near = 1.0f;
    static const float far = 10.0f;
    static const float right = 2.0f/1.6f;
    static const float left = -2.0f/1.6f;
    static const float top = 1.0f/1.6f;
    static const float bottom = -1.0f/1.6f;
    //~ A3D::Ortho(ProjectionMatrix, left, right, bottom, top, near, far);
    A3D::Frustum(ProjectionMatrix, left, right, bottom, top, near, far);
    initRotationStep();
}
//~ #define PROFILING
void loop(void)
{
    #ifdef PROFILING
    long us;
    #endif
    fb.clear();
    #ifdef PROFILING
    Serial.println("Calculate new ModelView");
    us = micros();
    #endif
    animateCube();
    #ifdef PROFILING
    us = micros() - us;
    Serial.print("done, ");
    Serial.print(us);
    Serial.println(" microseconds taken");
    Serial.println("Model to world:");
    ModelWorldMatrix.print(Serial);
    Serial.println("Scale:");
    ScaleMatrix.print(Serial);
    Serial.println("Move:");
    MoveMatrix.print(Serial);
    Serial.println("World to view:");
    WorldViewMatrix.print(Serial);
    Serial.println("Projection:");
    ProjectionMatrix.print(Serial);
    delay(1000);
    Serial.println("Draw cube");
    us = micros();
    #endif
    for (uint8_t i = 0; i < num_cubes; ++i)
    {
        drawCube(i);
    }
    #ifdef PROFILING
    us = micros() - us;
    Serial.print("done, ");
    Serial.print(us);
    Serial.println(" microseconds taken");
    delay(1000);
    Serial.println("Flushing framebuffer");
    us = micros();
    #endif

    uint8_t buf[10*2];
    for (uint8_t i = 0; i < 10; ++i)
    {
        buf[i] = 0xAA;
        //~ buf[i] = 0xFF;
        buf[i+10] = 0x55;
        //~ buf[i+10] = 0xFF;
    }
    //~ static uint8_t h = 0;
    //~ fb.flush();

    static long frame_counter = 0;
    static long time_counter = millis();
    long new_time = millis();
    ++frame_counter;
    static float fps = 0.f;
    if (new_time - time_counter > 1000)
    {
        fps = (frame_counter * 1000.f) / (new_time - time_counter);
        time_counter = new_time;
        frame_counter = 0;
    }

    char fps_str[30];
    sprintf(fps_str, "fps: %4.3f", fps);
    char test_str[] = "Hej detta är ett\ntest åäö hopp";
    fb.text(0, 0, sizeof(fps_str), fps_str, 255, Fonts::font3x5, false);
    fb.text(0, 30, sizeof(test_str), test_str, 255, Fonts::font3x5, false);
    long n = Get_sys_count();
    fb.flush();
    n = cpu_cy_2_us(Get_sys_count() - n, 60000000);
    sprintf(fps_str, "Flush: %9ld us", n);
    fb.text(0, 6, sizeof(fps_str), fps_str, 255, Fonts::font3x5, false);
    fb.flush();
    #ifdef PROFILING
    us = micros() - us;
    Serial.print("done, ");
    Serial.print(us);
    Serial.println(" microseconds taken");
    delay(1000);
    #endif
}

int main(void)
{
    setup();
    for (;;) //ever
    {
        loop();
    }
    return 0;
}
