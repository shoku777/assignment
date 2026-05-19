#ifndef GAME_HPP
#define GAME_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "PuzzleBoard.hpp"

namespace ftxui {

class Game : public ComponentBase {
private:
    PuzzleBoard board_;
    int moves_;
    bool game_won_;
    ScreenInteractive* screen_;
    
    Component button_reset_;
    Component button_quit_;
    Component container_;
    
    Element RenderBoard();
    Element RenderStats();
    void ResetGame();
    
public:
    Game();
    ~Game() override = default;
    
    Element Render() override;
    bool OnEvent(Event event) override;
};

}  // namespace ftxui

#endif