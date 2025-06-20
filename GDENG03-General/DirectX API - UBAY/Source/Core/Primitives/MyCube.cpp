#include "Core/Primitives/MyCube.hpp"

using namespace DX3D;


//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
MyCube::MyCube() : faces{
    //* FRONT
    MyQuad(MyTriangle(MyVertex(0.5f,0.5f,0.5f),MyVertex(0.5f,-0.5f,0.5f),MyVertex(0.5f,0.5f,0.5f)),
           MyTriangle(MyVertex(0.5f,0.5f,0.5f),MyVertex(0.5f,0.5f,0.5f),MyVertex(-0.5f,0.5f,0.5f))),
    //* BACK
    MyQuad(MyTriangle(MyVertex(0.5f,-0.5f,-0.5f),MyVertex(-0.5f,-0.5f,-0.5f),MyVertex(-0.5f,0.5f,-0.5f)), 
           MyTriangle(MyVertex(0.5f,-0.5f,-0.5f),MyVertex(-0.5f,0.5f,-0.5f),MyVertex(0.5f,0.5f,-0.5f))),
    //* LEFT
    MyQuad(MyTriangle(MyVertex(-0.5f,-0.5f,-0.5f),MyVertex(-0.5f,-0.5f,0.5f),MyVertex(-0.5f,0.5f,0.5f)), 
           MyTriangle(MyVertex(-0.5f,-0.5f,-0.5f),MyVertex(-0.5f,0.5f,0.5f),MyVertex(-0.5f,-0.5f,0.5f))),
    //* RIGHT
    MyQuad(MyTriangle(MyVertex(0.5f,-0.5f,0.5f),MyVertex(0.5f,-0.5f,-0.5f),MyVertex(0.5f,0.5f,-0.5f)), 
           MyTriangle(MyVertex(0.5f,-0.5f,0.5f),MyVertex(0.5f,0.5f,-0.5f),MyVertex(0.5f,0.5f,0.5f))),
    //* TOP
    MyQuad(MyTriangle(MyVertex(-0.5f,0.5f,0.5f),MyVertex(0.5f,0.5f,0.5f),MyVertex(0.5f,0.5f,-0.5f)),
           MyTriangle(MyVertex(-0.5f,0.5f,0.5f),MyVertex(0.5f,0.5f,-0.5f),MyVertex(-0.5f,0.5f,-0.5f))),
    //* BOTTOM
    MyQuad(MyTriangle(MyVertex(-0.5f,-0.5f,-0.5f),MyVertex(0.5f,-0.5f,-0.5f),MyVertex(0.5f,-0.5f,0.5f)), 
           MyTriangle(MyVertex(-0.5f,-0.5f,-0.5f),MyVertex(0.5f,-0.5f,0.5f),MyVertex(-0.5f,-0.5f,0.5f)))
}, position(MyVec3(0.0f)) {
}
MyCube::~MyCube() {}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝
