# 银晓的 C++ 玩具

这里堆一些没事干的时候写的玩具代码，仅当**娱乐**罢了（  

## 编译选项

介于银晓不止写写 C With STL，所以大部分项目都是基于 **Modern C++** 开发的  
请确保你的 IDE 或者编译器开启了 C++11 或者更高的 C++ 标准，或者加入如下编译参数  
```text
-std=c++11
```
部分项目使用了 C++20 甚至是 C++23 的新特性 *例如说 `std::ranges`*  
请查看相应项目的 `README.md` 以获得编译所需的版本要求

## 仓库内容  

- 高精度整数计算库 `./HightPrecisionLib/Integer`
- 一个功能非常简单的程序计时器 `./Timer`
- 部分 STL 容器的输出流重载 `./EasyCout`
- C++ 字符串切片汇总 `./StringSplits`
- 2048 游戏 Demo `./Game2048Demo`
