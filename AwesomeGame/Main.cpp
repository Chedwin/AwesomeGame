#include "Main.h"
using namespace GAME;

int main(int argc, char* argv[]) {
	// Make sure we're not running on a 64-bit machine
	static_assert(sizeof(void*) == 4, "64-bit code generation not supported!\n");

	Debug::Init(); // create the debug file if it doesn't already exist
	GameSceneManager::getInstance()->Run();

	exit(0);
}
