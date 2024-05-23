// From: https://stackoverflow.com/questions/26328793/how-to-split-string-with-delimiter-using-c

#include <algorithm>
#include <iostream>
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
 * @brief C++ 98 及以前的传统 Split
 * @param s 被分割的字符串
 * @param tokens 分隔后的结果
 * @param delimiters 分隔符
 *********************************/
void split(const std::string& s, std::vector<std::string>& tokens,
           const std::string& delimiters = " ") {
  std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
  std::string::size_type pos = s.find_first_of(delimiters, lastPos);
  while (std::string::npos != pos || std::string::npos != lastPos) {
    tokens.push_back(
        s.substr(lastPos, pos - lastPos));  // use emplace_back after C++11
    lastPos = s.find_first_not_of(delimiters, pos);
    pos = s.find_first_of(delimiters, lastPos);
  }
}
