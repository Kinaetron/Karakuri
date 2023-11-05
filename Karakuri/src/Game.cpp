#include "Game.h"
#include <iostream>

Game::Game(std::string title, int width, int height)
{
	std::cout << "The title is: " << title << std::endl;
	std::cout << "The window width is: " << width << std::endl;
	std::cout << "The window height is: " << height << std::endl;
}
