#include "Config.hpp"
#include <iostream>
#include "Game.hpp"
#include <string>

int main() {
	std::cout << "Jump height : " << JumpHeight << std::endl;
	std::cout << "Jump duration : " << JumpDuration << std::endl;

	Update();

	return 0;
}
