cmake_minimum_required(VERSION 3.14)
project(NumberPuzzleGame)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

add_executable(puzzle_game
    src/main.cpp
    src/Game.cpp
    src/PuzzleBoard.cpp
)

target_link_libraries(puzzle_game
    ftxui::screen
    ftxui::dom
    ftxui::component
)