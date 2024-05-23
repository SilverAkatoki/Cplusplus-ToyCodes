#include <algorithm>
#include <iostream>
#include <ranges>  // NOLINT
#include <string>
#include <vector>

void split(const std::string& s, std::vector<std::string>& tokens,
           const std::string& delimiters);

int main() {
  std::vector<std::string> split_res;
  split("abbabb", split_res, "b");
  std::for_each(split_res.begin(), split_res.end(),
                [](auto ch) { std::cout << ch << ' '; });
  system("pause");
  return 0;
}

/**********************************
 * @brief C++ 23 基于 Ranges 库的 Split
 * @param s 被分割的字符串
 * @param tokens 分隔后的结果
 * @param delimiters 分隔符
 *********************************/
void split(const std::string& s, std::vector<std::string>& tokens,
           const std::string& delimiters = " ") {
  tokens = s | std::ranges::views::split(delimiters) |
             std::ranges::views::transform(
                 [](auto&& i) { return i | std::ranges::to<std::string>(); }) |
             std::ranges::to<std::vector>();
}
