#include <Game/MyGame.h>
#include <Window/MyWindow.h>
#include <Graphics/MyGraphicsEngine.h>
#include <Core/MyLogger.h>
#include <Game/MyDisplay.h>

//* ╔════════════════════════════╗
//* ║ Constructors & Destructors ║
//* ╚════════════════════════════╝

DX3D::MyGame::MyGame(const GameDesc& desc) :
	MyBase({ *std::make_unique<MyLogger>(desc.logLevel).release() }),
	loggerPtr(&logger) {
	graphicsEngine = std::make_unique<MyGraphicsEngine>(GraphicsEngineDesc{logger });
	display = std::make_unique<MyDisplay>(DisplayDesc{ {logger,desc.windowSize},graphicsEngine->getGraphicsDevice() });

	DX3DLogInfo("MyGame initialized.");
}

DX3D::MyGame::~MyGame() {
	DX3DLogInfo("MyGame is shutting down...");
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void DX3D::MyGame::onInternalUpdate() {
	graphicsEngine->render(display->getSwapChain());
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝