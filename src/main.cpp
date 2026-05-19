#include <ftxui/component/screen_interactive.hpp>
#include "Game.hpp"

int main() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    
    auto game = ftxui::Game();
    
    screen.Loop(game);
    
    return 0;
}