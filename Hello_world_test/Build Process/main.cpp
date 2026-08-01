#include "Config.hpp"
#include <iostream>
#include "Game.hpp"

int main() {
	std::cout << "Jump height : " << JumpHeight << std::endl;
	std::cout << "Jump duration : " << JumpDuration << std::endl;

	Update();

	return 0;
}