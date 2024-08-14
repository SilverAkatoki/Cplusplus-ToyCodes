// Copyleft 2024 银晓 SilverAkatoki
// MIT License
// C++ 17 以后均可编译

#if __cplusplus >= 201703L

#ifndef GAME_2048_H
#define GAME_2048_H

#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#define GAME_WINING_NUM 2048

namespace game2048 {

/**
 * @brief 随机生成整数的工具类
 */
class RandInt {
 public:
  RandInt();

  /**
   * @brief 生成随机整数的方法
   * @param low 随机数的最小值（默认为 0）
   * @param hight 随机数的最大值（默认为 1）
   * @return 在给定范围内生成的随机整数
   */
  inline int Random(const int &low = 0, const int &hight = 1);

 private:
  std::random_device rd;
  std::mt19937 generator;
};

/**
 * @brief 2048 游戏的主类
 */
class Game {
 public:
  enum class Direction { Up, Down, Left, Right };
  enum class GameType {
    Lost = -1,  // 无法继续合并并且游戏区域已占满
    StillPlay,  // 仍可继续合并或是添加新的数字
    Wining      // 游戏胜利
  };

  Game();
  Game(const size_t &column, const size_t &row);

  /**
   * @brief 在标准输出流中打印当前的游戏情况
   */
  void Print() const noexcept;

  /**
   * @brief 向指定方向移动游戏区域
   * @param direction 移动方向的枚举值，类型为 `game2048::Game::Direction`
   * @return 游戏当前游玩状态的枚举值，类型为 `game2048::Game::GameType`
   */
  GameType Move(const Direction &direction);

 private:
  size_t map_width;                         // 游戏区域宽度
  size_t map_height;                        // 游戏区域高度
  int16_t wining_target = GAME_WINING_NUM;  // 最终胜利所合成的数
  std::vector<std::vector<int16_t>> board;  // 游戏区域
  RandInt rdi;                              // 随机数生成器

  /**
   * @brief 向游戏区域内添加新的数字
   */
  void AddNewNum() noexcept;

  void MoveLeft() noexcept;
  void MoveRight() noexcept;
  void MoveUp() noexcept;
  void MoveDown() noexcept;

  void MergeRow(std::vector<int16_t> *row) noexcept;
  inline void ReverseRow(std::vector<int16_t> *row) noexcept;

  GameType IsWining() const noexcept;
};

}  // namespace game2048

#endif  // GAME_2048_H

#endif
