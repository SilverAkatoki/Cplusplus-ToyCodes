#include <iostream>

#include "hp_int.h"  // NOLINT

int main() {
  hp::Num num1 = 21;
  hp::Num num2 = 21;
  std::cout << num1 << " + " << num2 << " = " << num1 + num2 << '\n';
  std::cout << num1 << " - " << num2 << " = " << num1 - num2 << '\n';
  std::cout << num1 << " * " << num2 << " = " << num1 * num2 << '\n';
  std::cout << num1 << " / " << num2 << " = " << num1 / num2 << '\n';
  std::cout << num1 << " % " << num2 << " = " << num1 % num2 << '\n';
  int index = 12;
  std::cout << num1 << " ^ " << index << " = " << pow(num1, 12) << '\n';
  std::cout << '-' << num1 << "= " << -num1 << '\n';
  std::cout << "|" << num1 << "| = " << abs(num1) << '\n';
  system("pause");
  return 0;
}
