#include <bits/stdc++.h>

#include "easy_cout.h"  // NOLINT

int main() {
  using namespace std;  // NOLINT

  // std::vector<int> test[]{{1}, {2}, {3}, {4}, {5}};
  // std::vector<int> test{1, 2, 3, 4, 5};
  // std::vector<std::vector<int>> test;
  // std::vector<vector<int>> test{{1}, {2, 3}};
  // std::tuple<int, std::tuple<int>> test{1, {2}};
  // std::unordered_map<int, std::vector<int>> test{{1, {2}}, {3, {4}}};
  // std::pair<
  //     int,
  //     pair<int, pair<int, pair<int, pair<int, pair<int, pair<int,
  //     int>>>>>>> test{1, {2, {3, {4, {5, {6, {7, 8}}}}}}};
  unordered_set<int> test{1, 2, 3, 4};
  cout << test << ' ' << test << '\n';
  system("pause");
  return 0;
}
