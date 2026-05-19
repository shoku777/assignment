#include "PuzzleBoard.hpp"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

PuzzleBoard::PuzzleBoard() {
    board_.resize(4, std::vector<int>(4));
    Initialize();
}

void PuzzleBoard::Initialize() {
    int counter = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            board_[i][j] = counter++;
        }
    }
    board_[3][3] = 0;
    empty_pos_ = {3, 3};
    Shuffle(200);
}

void PuzzleBoard::Shuffle(int moves) {
    std::vector<Direction> dirs = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    
    for (int i = 0; i < moves; ++i) {
        Direction dir = dirs[dis(gen)];
        Move(dir);
    }
}

void PuzzleBoard::FindEmptyPosition() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board_[i][j] == 0) {
                empty_pos_ = {i, j};
                return;
            }
        }
    }
}

bool PuzzleBoard::IsValidMove(int row, int col) const {
    return row >= 0 && row < 4 && col >= 0 && col < 4;
}

void PuzzleBoard::Swap(int row1, int col1, int row2, int col2) {
    std::swap(board_[row1][col1], board_[row2][col2]);
}

bool PuzzleBoard::Move(Direction dir) {
    int new_row = empty_pos_.first;
    int new_col = empty_pos_.second;
    
    switch(dir) {
        case Direction::UP:
            new_row = empty_pos_.first - 1;
            break;
        case Direction::DOWN:
            new_row = empty_pos_.first + 1;
            break;
        case Direction::LEFT:
            new_col = empty_pos_.second - 1;
            break;
        case Direction::RIGHT:
            new_col = empty_pos_.second + 1;
            break;
        default:
            return false;
    }
    
    if (!IsValidMove(new_row, new_col)) {
        return false;
    }
    
    Swap(empty_pos_.first, empty_pos_.second, new_row, new_col);
    empty_pos_ = {new_row, new_col};
    return true;
}

bool PuzzleBoard::IsSolved() const {
    int expected = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == 3 && j == 3) {
                if (board_[i][j] != 0) return false;
            } else {
                if (board_[i][j] != expected++) return false;
            }
        }
    }
    return true;
}

int PuzzleBoard::GetValue(int row, int col) const {
    return board_[row][col];
}

int PuzzleBoard::GetTargetValue(int row, int col) const {
    if (row == 3 && col == 3) return 0;
    return row * 4 + col + 1;
}

void PuzzleBoard::Print() const {
    for (const auto& row : board_) {
        for (int val : row) {
            std::cout << (val == 0 ? "  " : std::to_string(val)) << "\t";
        }
        std::cout << std::endl;
    }
}