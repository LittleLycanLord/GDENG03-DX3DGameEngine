#include "Core/MyBase.h"
#include "Core/MyLogger.h"
using namespace DX3D;

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝
DX3D::MyBase::MyBase(const BaseDescription& desc) :logger(desc.logger) {
}

DX3D::MyBase::~MyBase() {
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
MyLogger& DX3D::MyBase::getLogger() noexcept {
	return logger;
}
