#pragma once

namespace DX3D {
    struct MyVec3 {
        float x, y, z;

        MyVec3() : x(0), y(0), z(0) {}
        MyVec3(float all) : x(all), y(all), z(all) {}
        MyVec3(float x, float y, float z) : x(x), y(y), z(z) {}
    };
} // namespace DX3D

