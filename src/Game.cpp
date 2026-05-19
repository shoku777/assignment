#include "Game.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <sstream>

namespace ftxui {

Game::Game() : moves_(0), game_won_(false) {
    ResetGame();
    main_component_ = CreateGameComponent();
}

void Game::ResetGame() {
    board_.Initialize();
    moves_ = 0;
    game_won_ = false;
}

Component Game::CreateGameComponent() {
    auto renderer = Renderer([this] {
        // 构建游戏板 - 使用最简单的文本格式
        std::vector<std::string> board_lines;
        for (int i = 0; i < 4; ++i) {
            std::string line;
            for (int j = 0; j < 4; ++j) {
                int value = board_.GetValue(i, j);
                if (value == 0) {
                    line += "    ";
                } else if (value < 10) {
                    line += "  " + std::to_string(value) + " ";
                } else {
                    line += " " + std::to_string(value) + " ";
                }
                if (j < 3) line += "|";
            }
            board_lines.push_back(line);
        }
        
        // 转换为 FTXUI 元素
        std::vector<Element> board_elements;
        for (const auto& line : board_lines) {
            board_elements.push_back(text(line) | center);
            board_elements.push_back(separator());
        }
        
        // 移除最后一个多余的 separators
        if (!board_elements.empty()) {
            board_elements.pop_back();
        }
        
        // 统计信息
        std::stringstream ss;
        ss << "Moves: " << moves_;
        if (game_won_) {
            ss << "  >>> YOU WIN! <<<";
        } else {
            ss << "  |  Playing...";
        }
        
        auto stats = text(ss.str()) | bold | color(Color::Yellow) | center;
        
        // 控制说明
        auto controls = text("WASD or Arrow Keys = Move | R = Reset | Q = Quit") 
                        | center | color(Color::GrayLight);
        
        // 标题
        auto title = text("=== NUMBER PUZZLE ===") | bold | color(Color::Cyan) | center;
        
        // 整个界面
        auto layout = vbox({
            title,
            separator(),
            stats,
            separator(),
            vbox(board_elements),
            separator(),
            controls,
        }) | border | size(WIDTH, GREATER_THAN, 50);
        
        return layout;
    });
    
    renderer |= CatchEvent([this](Event event) {
        // 退出
        if (event == Event::Character('q') || event == Event::Character('Q')) {
            exit(0);
            return true;
        }
        
        // 重置
        if (event == Event::Character('r') || event == Event::Character('R')) {
            ResetGame();
            return true;
        }
        
        // 胜利后不能再移动
        if (game_won_) {
            return false;
        }
        
        // 移动
        MoveDirection dir = MoveDirection::None;
        
        if (event == Event::ArrowUp || event == Event::Character('w') || event == Event::Character('W')) {
            dir = MoveDirection::Up;
        } else if (event == Event::ArrowDown || event == Event::Character('s') || event == Event::Character('S')) {
            dir = MoveDirection::Down;
        } else if (event == Event::ArrowLeft || event == Event::Character('a') || event == Event::Character('A')) {
            dir = MoveDirection::Left;
        } else if (event == Event::ArrowRight || event == Event::Character('d') || event == Event::Character('D')) {
            dir = MoveDirection::Right;
        }
        
        if (dir != MoveDirection::None && board_.Move(dir)) {
            moves_++;
            if (board_.IsSolved()) {
                game_won_ = true;
            }
            return true;
        }
        
        return false;
    });
    
    return renderer;
}

void Game::Run() {
    auto screen = ScreenInteractive::Fullscreen();
    screen.Loop(main_component_);
}

}  // namespace ftxui