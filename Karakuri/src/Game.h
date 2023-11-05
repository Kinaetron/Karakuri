#ifndef GAME_H
#define GAME_H

#include <string>

#ifdef KARAKURI_EXPORTS
#define KARAKURI_API __declspec(dllexport)
#else
#define KARAKURI_API __declspec(dllimport)
#endif

class KARAKURI_API Game
{
public:
	Game(std::string title, int width, int height);
};

#endif