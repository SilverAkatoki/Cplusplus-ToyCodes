#include "Game2048.h"

game2048::Game::Game() : Game(4, 4) {}

game2048::Game::Game(const size_t &column, const size_t &row)
    : map_width(column),
      map_height(row),
      board(map_height, std::vector<int16_t>(map_width, 0)) {
  for (auto i = 0; i < 2; ++i) {
    AddNewNum();
  }
}

void game2048::Game::Print() const noexcept {
  for (const auto &row : board) {
    for (const auto &num : row) {
      std::cout << (num == 0 ? "." : std::to_string(num)) << " ";
    }
    std::endl(std::cout);
  }
}

game2048::Game::GameType game2048::Game::Move(
    const game2048::Game::Direction &direction) {
  static void (game2048::Game::*functions[4])() = {
      &game2048::Game::MoveUp, &game2048::Game::MoveDown,
      &game2048::Game::MoveLeft, &game2048::Game::MoveRight};

  if (auto game_type = IsWining(),
      game2048 != game2048::Game::GameType::StillPlay) {
    return game_type;
  }

  size_t index = static_cast<int>(direction);
  if (index < 0 || index >= 4) {
    throw std::invalid_argument("跳转错误");
  }

  (this->*functions[index])();

  AddNewNum();
  return game2048::Game::GameType::StillPlay;
}

void game2048::Game::AddNewNum() noexcept {
  std::vector<std::pair<int16_t, int16_t>> empty_positions{};
  for (size_t i = 0; i < map_height; ++i) {
    for (size_t j = 0; j < map_width; ++j) {
      if (board[i][j] == 0) {
        empty_positions.emplace_back(i, j);
      }
    }
  }

  if (!empty_positions.empty()) {
    auto random_index = rdi.Random(0, empty_positions.size() - 1);
    auto [x, y] = empty_positions[random_index];
    board[x][y] = 2;
  }
}

void game2048::Game::MoveLeft() noexcept {
  for (auto &row : board) {
    MergeRow(&row);
  }
}

void game2048::Game::MoveRight() noexcept {
  for (auto &row : board) {
    ReverseRow(&row);
    MergeRow(&row);
    ReverseRow(&row);
  }
}

void game2048::Game::MoveUp() noexcept {
  for (size_t j = 0; j < map_width; ++j) {
    std::vector<int16_t> column(map_height);
    for (size_t i = 0; i < map_height; ++i) {
      column[i] = board[i][j];
    }
    MergeRow(&column);
    for (size_t i = 0; i < map_height; ++i) {
      board[i][j] = column[i];
    }
  }
}

void game2048::Game::MoveDown() noexcept {
  for (size_t j = 0; j < map_width; ++j) {
    std::vector<int16_t> column(map_height);
    for (size_t i = 0; i < map_height; ++i) {
      column[i] = board[i][j];
    }
    ReverseRow(&column);
    MergeRow(&column);
    ReverseRow(&column);
    for (size_t i = 0; i < map_height; ++i) {
      board[i][j] = column[i];
    }
  }
}

void game2048::Game::MergeRow(std::vector<int16_t> *row) noexcept {
  std::vector<int16_t> merged_row(map_width);

  size_t merged_index = 0;
  for (size_t i = 0; i < map_width; ++i) {
    if ((*row)[i] != 0) {
      if (merged_index > 0 && merged_row[merged_index - 1] == (*row)[i]) {
        merged_row[merged_index - 1] *= 2;
      } else {
        merged_row[merged_index++] = (*row)[i];
      }
    }
  }

  while (merged_index < map_width) {
    merged_row[merged_index++] = 0;
  }

  *row = merged_row;
}

// 少写两个方向的代码
inline void game2048::Game::ReverseRow(std::vector<int16_t> *row) noexcept {
  std::reverse(row->begin(), row->end());
}

game2048::Game::GameType game2048::Game::IsWining() const noexcept {
  // 出现 2048 即胜利，有 0 说明还能合
  for (const auto &row : board) {
    for (const auto &num : row) {
      if (num == wining_target) {
        return GameType::Wining;
      } else if (num == 0) {
        return GameType::StillPlay;
      }
    }
  }

  // 合并检查
  for (size_t i = 0; i < map_height; ++i) {
    for (size_t j = 0; j < map_width; ++j) {
      if ((i + 1 < map_height && board[i][j] == board[i + 1][j]) ||
          (j + 1 < map_width && board[i][j] == board[i][j + 1])) {
        return GameType::StillPlay;
      }
    }
  }

  return GameType::Lost;
}

game2048::RandInt::RandInt() : rd(), generator(rd()) {}

inline int game2048::RandInt::Random(const int &low, const int &hight) {
  if (low > hight) throw std::invalid_argument("");
  std::uniform_int_distribution<int> distribution(low, hight);
  return distribution(generator);
}
