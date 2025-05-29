#pragma once
#include "Math/MyMatrix4x4.hpp"

// namespace DX3D {
//     __declspec(align(16))
//         struct MyConstant {
//         MyMatrix4x4 world;
//         MyMatrix4x4 view;
//         MyMatrix4x4 projection;
//         float angle;
//     };
// } // namespace DX3D

namespace DX3D {
    __declspec(align(16))
        struct MyConstant {
        float angle;
    };
} // namespace DX3D

