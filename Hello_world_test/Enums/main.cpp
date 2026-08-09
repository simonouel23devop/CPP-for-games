#include <iostream>
#include <cstdint>
#include <type_traits>

enum day
{
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday
};

int day = Monday;

enum class Color : uint32_t
{
	Black = 0x000000,
	Red =  0xFF0000,
	Green = 0x00FF00,
	Blue = 0x0000FF,
	White = 0xFFFFFFFF,
	LightGrey = 0xD3D3D3
};

Color red = Color::Red;

auto green = static_cast<uint32_t>(Color::Green); // Conversion explicite, car Color est un enum class
Color blue = static_cast<Color>(2); // Conversion explicite, car Color est un enum class

enum class GameState : uint8_t
{
	MainMenu,
	Game,
	GameOver,
	Highscores
};

void DoMainMenu();
void DoGame();



int main()
{
	
	GameState gamestate = GameState::MainMenu;

	switch (gamestate)
	{
	case GameState::MainMenu:
		DoMainMenu();
		break;
	case GameState::Game:
		DoGame();
		break;
	case GameState::GameOver:
		break;
	case GameState::Highscores:
		break;

	}


	return 0;
}