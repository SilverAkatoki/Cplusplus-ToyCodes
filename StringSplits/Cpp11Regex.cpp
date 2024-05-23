#include <algorithm>
#include <iostream>
#include <regex>
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

// ! TODO 正则版本的 Split

/**
 * @brief
 * @param s
 * @param tokens
 * @param delimiters
 */
void split(const std::string& s, std::vector<std::string>& tokens,
           const std::string& delimiters = " ") {
  tokens = std::vector<std::string>(
      std::sregex_token_iterator(s.begin(), s.end(), std::regex("\\s+"), -1),
      std::sregex_token_iterator());
}
