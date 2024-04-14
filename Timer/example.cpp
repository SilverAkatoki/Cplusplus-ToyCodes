#include <iostream>

#include "timer.h"  // NOLINT

int main() {
  timer::Timer<timer::ms> test_timer;
  test_timer.start();
  for (int i = 0; i < INT_MAX; ++i) {
    if (i == INT_MAX / 2) {
      test_timer.continued();
      std::cout << "Continued now!\n";
    }
    if (i == INT_MAX / 3) {
      test_timer.paused();
      std::cout << "Paused now!\nThe timer is " << test_timer.get() << '\n';
    }
    // Do something.
  }
  test_timer.end();
  std::cout << test_timer.get() << '\n';
  test_timer.reset();
  std::cout << "The timer was reseted.\n";
  system("pause");
  return 0;
}
