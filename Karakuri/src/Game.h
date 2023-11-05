#ifndef GAME_H
#define GAME_H

#include <string>

#ifdef MATHLIBRARY_EXPORTS
#define KARAKURI_API __declspec(dllexport)
#else
#define KARAKURI_API __declspec(dllimport)
#endif

extern "C" KARAKURI_API void Game(std::string title, int width, int height);

#endif