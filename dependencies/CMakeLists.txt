include(FetchContent)

# Set SDL_SHARED and SDL_STATIC before fetching the content
set(SDL_SHARED OFF CACHE BOOL "Build SDL as a shared library" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build SDL as a static library" FORCE)

# Set SDL_mixer shared/static options
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build the library as a shared library" FORCE)


# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG 5e59b396b0b9e0245e0f47b9878dfe547e34fb26 # compiled_only
)

# SDL
FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG 2eef7ca475decd2b864214cdbfe72b143b16d459 # 2.30.5
)

# SDL Mixer
FetchContent_Declare(
    SDL_Mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG a37e09f85d321a13dfcf0d4432827ee09beeb623 # 2.8.0
)

FetchContent_MakeAvailable(spdlog SDL SDL_Mixer)