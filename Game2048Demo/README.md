# README - 2048 游戏 Demo

2048 的后台代码，并没有任何可供游玩的部分  
*加了捕捉操作就能玩了*

## 命名空间相关
请记住以下涉及的所有代码均在 `game2048` 下  
为确保语义清晰，本文档显式写出所有命名空间  
当然你可以使用一些~~禁术~~来少写一点代码：  

```cpp
using namespace game2048;
```

*小心命名空间重名*

## 初始化

使用如下代码创建一个游戏对象

```cpp{.line-numbers}
game2048::Game game;
game2048::Game game1(2, 4);
```

构造函数的可选参数为：

- `column` 决定游戏区域的**宽度**（默认为 $4$ ）
- `row` 决定游戏区域的**长度**（默认为 $4$ ）

## 可用方法一览

### `Print()`

向标准输出流中**打印**当前游戏区域的方法。
打印的格式如下：

```text
. 2 . .
. . . .
2 . . .
. . . .
```

### `Move(...)`

**移动**游戏区域的函数。
只有一个必填的参数：

| 值 | 含义 |
| :---: | :---: |
|  `game2048::Game::Direction::Up` | 向上移动  |
| `game2048::Game::Direction::Down` | 向下移动 |
| `game2048::Game::Direction::Left` | 向左移动 |
| `game2048::Game::Direction::Right` | 向右移动 |

返回值是游戏的**输赢情况**：

| 值 | 含义 |
| :---: | :---: |
|  `game2048::Game::GameWining::Lost` | 游戏失败  |
|  `game2048::Game::GameWining::StillPlay` | 游戏仍可以继续游玩  |
| `game2048::Game::GameWining::Wining` | 游戏胜利 |
