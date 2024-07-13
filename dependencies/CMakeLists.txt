include(FetchContent)

# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG 5e59b396b0b9e0245e0f47b9878dfe547e34fb26 # compiled_only
)

FetchContent_MakeAvailable(spdlog)