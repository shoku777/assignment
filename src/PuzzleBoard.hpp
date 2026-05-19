#ifndef PUZZLE_BOARD_HPP
#define PUZZLE_BOARD_HPP

#include <vector>
#include <utility>

enum class Direction {
    UP, DOWN, LEFT, RIGHT, NONE
};

class PuzzleBoard {
private:
    std::vector<std::vector<int>> board_;
    std::pair<int, int> empty_pos_;
    
    void FindEmptyPosition();
    bool IsValidMove(int row, int col) const;
    void Swap(int row1, int col1, int row2, int col2);
    
public:
    PuzzleBoard();
    ~PuzzleBoard() = default;
    
    void Initialize();
    void Shuffle(int moves = 100);
    
    bool Move(Direction dir);
    bool IsSolved() const;
    
    int GetValue(int row, int col) const;
    int GetTargetValue(int row, int col) const;
    
    void Print() const;
};

#endif