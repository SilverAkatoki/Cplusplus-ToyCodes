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
 * @brief C++ 20 基于 Ranges 库的 Split
 * @param s 被分割的字符串
 * @param tokens 分隔后的结果
 * @param delimiters 分隔符
 *********************************/
void split(const std::string& s, std::vector<std::string>& tokens,
           const std::string& delimiters = " ") {
  std::ranges::copy(
      s | std::views::split(delimiters) | std::views::transform([](auto word) {
        return std::string(word.begin(), word.end());
      }) | std::views::filter([](std::string word) { return word != ""; }),
      std::back_inserter(tokens));
}
