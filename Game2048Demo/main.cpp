#include "Game2048.h"

int main() {
  game2048::Game game;
  game.Print();

  for (int i = 0; i < 10; ++i) {
    // 向上移动
    std::cout << "向上移动后：" << std::endl;
    game.Move(game2048::Game::Direction::Up);
    game.Print();

    // 向下移动
    std::cout << "向下移动后：" << std::endl;
    game.Move(game2048::Game::Direction::Down);
    game.Print();

    // 向左移动
    std::cout << "向左移动后：" << std::endl;
    game.Move(game2048::Game::Direction::Left);
    game.Print();

    // 向右移动
    std::cout << "向右移动后：" << std::endl;
    game.Move(game2048::Game::Direction::Right);
    game.Print();
  }

  system("pause");
  return 0;
}
