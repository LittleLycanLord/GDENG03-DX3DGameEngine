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
	m_loggerPtr(&m_logger) {
	m_graphicsEngine = std::make_unique<MyGraphicsEngine>(GraphicsEngineDesc{ m_logger });
	m_display = std::make_unique<MyDisplay>(DisplayDesc{ {m_logger,desc.windowSize},m_graphicsEngine->getGraphicsDevice() });

	DX3DLogInfo("MyGame initialized.");
}

DX3D::MyGame::~MyGame() {
	DX3DLogInfo("MyGame is shutting down...");
}

//* ╔═══════════╗
//* ║ Functions ║
//* ╚═══════════╝
void DX3D::MyGame::onInternalUpdate() {
	m_graphicsEngine->render(m_display->getSwapChain());
}

//* ╔════════════════════════════════╗
//* ║ Virtual / Overridden Functions ║
//* ╚════════════════════════════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝