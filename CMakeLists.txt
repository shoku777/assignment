cmake_minimum_required(VERSION 3.14)
project(NumberPuzzleGame VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)


add_executable(puzzle_game
    src/main.cpp
    src/Game.cpp
    src/PuzzleBoard.cpp
)


target_link_libraries(puzzle_game
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)


target_include_directories(puzzle_game PRIVATE ${CMAKE_SOURCE_DIR}/src)