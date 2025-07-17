#pragma once
#include "Math/MyMatrix4x4.hpp"

namespace DX3D {
    // GPU constant buffer alignment - must be 16-byte aligned
    __declspec(align(16))
    struct MyConstant {
        MyMatrix4x4 world;
        MyMatrix4x4 view;
        MyMatrix4x4 projection;
        float time = 0.0f;
        float padding1 = 0.0f;  // Pad to 16-byte boundary
        float padding2 = 0.0f;  // Pad to 16-byte boundary  
        float padding3 = 0.0f;  // Pad to 16-byte boundary
    };
} // namespace DX3D

// namespace DX3D {
//     __declspec(align(16))
//         struct MyConstant {
//         float angle;
//     };
// } // namespace DX3D

