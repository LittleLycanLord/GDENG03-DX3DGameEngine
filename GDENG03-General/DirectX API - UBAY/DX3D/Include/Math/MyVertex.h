#pragma once
#include <Core/DX3DCore.h>
#include <Math/MyVec3.h>

namespace DX3D {
	class MyVertex {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
	public:
		MyVec3 position;

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		MyVertex() = default;
		MyVertex(MyVec3 position) : position(position) {}
		MyVertex(float x, float y, float z) : position(MyVec3(x, y, z)) {}

		//* ╔═══════════╗
		//* ║ Functions ║
		//* ╚═══════════╝
	private:
	public:

		//* ╔════════════════════════════════╗
		//* ║ Virtual / Overridden Functions ║
		//* ╚════════════════════════════════╝
	protected:
	public:

		//* ╔═══════════════════╗
		//* ║ Getters & Setters ║
		//* ╚═══════════════════╝
	public:
	};
} // namespace DX3D

