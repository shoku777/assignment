# 数字拼图游戏

一个基于 C++17 和 FTXUI 库开发的终端数字拼图游戏。

## 项目介绍

这是一个经典的 15 拼图游戏。在 4x4 的网格中，你需要将数字 1 到 15 按顺序排列，空格位于右下角。

特性：

- 键盘控制（方向键 / WASD）
- 自动记录移动步数
- 游戏重置功能
- 胜利检测

## 使用方法

### 游戏目标

将数字按 1 到 15 的顺序排列，空格在右下角。

### 操作按键

| 按键 | 功能 |
|------|------|
| ↑ 或 W | 向上移动 |
| ↓ 或 S | 向下移动 |
| ← 或 A | 向左移动 |
| → 或 D | 向右移动 |
| R | 重置游戏 |
| Q | 退出游戏 |

### 编译运行

克隆仓库：

git clone https://github.com/shoku777/assignment.git
cd assignment

编译：

mkdir build && cd build
cmake ..
make

运行：

./puzzle_game

### 系统要求

- CMake >= 3.14
- C++17 编译器
- FTXUI（编译时自动下载）

## 项目结构

assignment/
├── CMakeLists.txt
├── README.md
└── src/
    ├── main.cpp
    ├── Game.hpp
    ├── Game.cpp
    ├── PuzzleBoard.hpp
    └── PuzzleBoard.cpp

## 贡献指南

步骤：

1. Fork 本仓库
2. 创建特性分支：git checkout -b feature/新功能
3. 提交修改：git commit -m "添加新功能"
4. 推送分支：git push origin feature/新功能
5. 提交 Pull Request

代码规范：

- 使用 C++17 标准
- 保持代码缩进一致
- 添加必要注释

## 许可证

MIT License

## 作者

GitHub: shoku777
