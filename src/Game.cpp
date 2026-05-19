#include "Game.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/button.hpp>
#include <random>

namespace ftxui {

Game::Game() : moves_(0), game_won_(false) {
    screen_ = &ScreenInteractive::Fullscreen();
    ResetGame();
    
    auto reset_btn = Button("重置游戏", [this] { ResetGame(); });
    auto quit_btn = Button("退出游戏", [this] { screen_->Exit(); });
    
    button_reset_ = reset_btn;
    button_quit_ = quit_btn;
    
    container_ = Container::Horizontal({
        button_reset_,
        button_quit_,
    });
}

void Game::ResetGame() {
    board_.Initialize();
    moves_ = 0;
    game_won_ = false;
}

Element Game::RenderBoard() {
    std::vector<Element> rows;
    
    for (int i = 0; i < 4; ++i) {
        std::vector<Element> cells;
        for (int j = 0; j < 4; ++j) {
            int value = board_.GetValue(i, j);
            std::string content = (value == 0) ? "  " : std::to_string(value);
            
            auto cell = text(content) | center | size(WIDTH, EQUAL, 5) | size(HEIGHT, EQUAL, 3);
            
            if (value == 0) {
                cell = cell | color(Color::GrayDark) | bgcolor(Color::GrayLight);
            } else if (value == board_.GetTargetValue(i, j)) {
                cell = cell | color(Color::Green) | bgcolor(Color::Black);
            } else {
                cell = cell | color(Color::White) | bgcolor(Color::Blue);
            }
            
            cell = cell | border;
            cells.push_back(cell);
        }
        rows.push_back(hbox(cells));
    }
    
    return vbox(rows);
}

Element Game::RenderStats() {
    std::string moves_text = "移动步数: " + std::to_string(moves_);
    std::string status_text = game_won_ ? "🎉 胜利! 🎉" : "游戏中...";
    
    auto moves_element = text(moves_text) | bold | color(Color::Yellow);
    auto status_element = text(status_text) | bold | 
                          (game_won_ ? color(Color::Green) : color(Color::Cyan));
    
    return vbox({
        moves_element | center,
        separator(),
        status_element | center,
    }) | border;
}

Element Game::Render() {
    auto board_element = RenderBoard();
    auto stats_element = RenderStats();
    auto buttons_element = container_->Render() | center;
    
    auto main_layout = vbox({
        stats_element,
        separator(),
        board_element,
        separator(),
        buttons_element,
    }) | center | border;
    
    return main_layout;
}

bool Game::OnEvent(Event event) {
    if (game_won_) {
        if (event == Event::Character('r') || event == Event::Character('R')) {
            ResetGame();
            return true;
        }
        return container_->OnEvent(event);
    }
    
    Direction dir = Direction::NONE;
    
    if (event == Event::ArrowUp || event == Event::Character('w') || event == Event::Character('W')) {
        dir = Direction::UP;
    } else if (event == Event::ArrowDown || event == Event::Character('s') || event == Event::Character('S')) {
        dir = Direction::DOWN;
    } else if (event == Event::ArrowLeft || event == Event::Character('a') || event == Event::Character('A')) {
        dir = Direction::LEFT;
    } else if (event == Event::ArrowRight || event == Event::Character('d') || event == Event::Character('D')) {
        dir = Direction::RIGHT;
    } else if (event == Event::Character('r') || event == Event::Character('R')) {
        ResetGame();
        return true;
    } else if (event == Event::Character('q') || event == Event::Character('Q')) {
        screen_->Exit();
        return true;
    }
    
    if (dir != Direction::NONE && board_.Move(dir)) {
        moves_++;
        if (board_.IsSolved()) {
            game_won_ = true;
        }
        return true;
    }
    
    return container_->OnEvent(event);
}

}