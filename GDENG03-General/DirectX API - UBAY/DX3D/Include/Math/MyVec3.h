#pragma once
#include <Core/DX3DCore.h>

namespace DX3D {
	class MyVec3 {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
	public:
		float x{}, y{}, z{};

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		MyVec3() = default;
		MyVec3(float x, float y, float z) : x(x), y(y), z(z) {}

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

