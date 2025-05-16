#pragma once
#include <Core/DX3DCore.h>

namespace DX3D {
	class MyRect {
		//* ╔════════════╗
		//* ║ Attributes ║
		//* ╚════════════╝
	private:
	public:
		int left{}, top{}, width{}, height{};

		//* ╔════════════════════════════╗
		//* ║ Constructors & Destructors ║
		//* ╚════════════════════════════╝
	public:
		MyRect() = default;
		MyRect(int width, int height) : left(0), top(0), width(width), height(height) {}
		MyRect(int left, int top, int width, int height) : left(left), top(top), width(width), height(height) {}

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

