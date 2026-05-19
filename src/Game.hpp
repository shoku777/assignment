#ifndef GAME_HPP
#define GAME_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "PuzzleBoard.hpp"

namespace ftxui {

class Game {
private:
    PuzzleBoard board_;
    int moves_;
    bool game_won_;
    Component main_component_;
    
    void ResetGame();
    Component CreateGameComponent();
    
public:
    Game();
    void Run();
};

}

#endif