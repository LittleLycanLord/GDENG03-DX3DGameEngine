#include <All.h>

int main() {
	try {
		DX3D::MyGame game({ {1280,720},DX3D::MyLogger::LogLevel::Info });
		game.run();
	}
	catch (const std::runtime_error&) {
		return EXIT_FAILURE;
	}
	catch (const std::exception&) {
		return EXIT_FAILURE;
	}
	catch (...) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}