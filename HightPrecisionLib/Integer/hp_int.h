// Copyleft 2024 银晓 SilverAkatoki
// C++ 11 and after

#if __cplusplus >= 200704L
// Some 🤡 are using C++ 98 when C++ 23 rules are pushed up.
// What can I say.

#ifndef HP_INT_H_
#define HP_INT_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>  // std::make_pair() 要用
#include <vector>

namespace hight_precision {

/******************************************************************
 * @brief A very big integer number which can be max than `int64_t`
 *****************************************************************/
class Num {
 public:
  Num();

  // 这里不能加 explic 来 ban 了隐式转换（尽管cpplint这样警告了）
  // 要不然就不能 hp::Num num = 1; 这样子初始化

  Num(const std::string &num);                       // NOLINT
  Num(const int &num) : Num(std::to_string(num)) {}  // NOLINT

  Num &operator=(const std::string &num);
  Num &operator=(const int &num);

  friend std::ostream &operator<<(std::ostream &os, const Num &num) {
    std::string integer_digits(num.rev_integer_digits_.rbegin(),
                               num.rev_integer_digits_.rend());
    if (num.is_minus_) {
      return os << '-' << integer_digits;
    } else {
      return os << integer_digits;
    }
  }

  friend std::istream &operator>>(std::istream &is, Num &num) {
    std::string temp;
    is >> temp;
    num.StringConstructFunc(temp);
    return is;
  }

  friend Num abs(const Num &num);

  friend Num pow(const Num &num, const int &index);

  bool operator>(const Num &num) const;
  bool operator>=(const Num &num) const;
  bool operator==(const Num &num) const;
  bool operator!=(const Num &num) const;
  bool operator<=(const Num &num) const;
  bool operator<(const Num &num) const;

  Num operator+(const Num &num);

  Num operator-();
  Num operator-(const Num &num);

  Num operator*(const Num &num);

  Num operator/(const Num &num);

  Num operator%(const Num &num);

  Num &operator++();
  Num operator++(int);

  Num &operator--();
  Num operator--(int);

  void operator+=(const Num &num);
  void operator-=(const Num &num);
  void operator*=(const Num &num);
  void operator/=(const Num &num);
  void operator%=(const Num &num);

 private:
  bool is_minus_;                   // Signed, postive num's value is false.
  std::string rev_integer_digits_;  // Liked this: 1234 is saved as "4321".

  void StringConstructFunc(const std::string &num);

  bool ManageSign(std::string *num_str);
  void ManageExtraZero(std::string *num_str);

  Num Plus(const Num &num1, const Num &num2);
  Num Sub(const Num &num1, const Num &num2);
  Num Multply(const Num &num1, const Num &num2);
  std::pair<Num, Num> Divided(const Num &num1, const Num &num2);
};

Num pow(const Num &num, const int &index);

Num abs(const Num &num);

}  // namespace hight_precision

namespace hp = hight_precision;

#endif  // BIGNUM_REDUCED_STRINGVER_HP_H_

// Default construct function will create a zero.
hight_precision::Num::Num() {
  this->rev_integer_digits_ = "0";
  this->is_minus_ = false;
}

inline hight_precision::Num::Num(const std::string &num) {
  StringConstructFunc(num);
}

hight_precision::Num &hight_precision::Num::operator=(const std::string &num) {
  StringConstructFunc(num);
  return *this;
}

hight_precision::Num &hight_precision::Num::operator=(const int &num) {
  StringConstructFunc(std::to_string(num));
  return *this;
}

bool hight_precision::Num::ManageSign(std::string *num_str) {
  bool is_minus = num_str->find("-") != num_str->npos;
  // Delete the sign before the numbers.
  *num_str = num_str->substr(num_str->find_first_not_of("+-"));
  return is_minus;
}

void hight_precision::Num::ManageExtraZero(std::string *num_str) {
  size_t not_zero_pos = num_str->find_first_not_of("0");

  // all digits are zero
  if (not_zero_pos == std::string::npos) {
    *num_str = "0";
    return;
  }

  *num_str = num_str->substr(not_zero_pos);
}

void hight_precision::Num::StringConstructFunc(const std::string &num) {
  if (num.find_first_not_of("0123456789+-") != num.npos) {
    throw std::invalid_argument("String must be a integer number");
  }
  std::string num_str = num;

  // Format the numbers string.
  this->is_minus_ = ManageSign(&num_str);
  ManageExtraZero(&num_str);

  // If the numbers string is filled with zero (liked this "0000000").
  if (std::all_of(num_str.begin(), num_str.end(),
                  [](char c) { return c == '0'; })) {
    this->is_minus_ = false;
    this->rev_integer_digits_ = "0";
    return;
  }

  this->rev_integer_digits_ = num_str;
  std::reverse(this->rev_integer_digits_.begin(),
               this->rev_integer_digits_.end());
}

bool hight_precision::Num::operator>(const hight_precision::Num &num) const {
  // Positive number must be bigger than negetive number, right?
  if (this->is_minus_ != num.is_minus_) {
    return num.is_minus_;
  }

  // When two numbers' sign are same (liked 3 > 2 or -2 > - 1).
  // The boolean's value will be true
  bool two_num_is_positive = !this->is_minus_;

  // The longer digits is, the bigger number is.
  if (this->rev_integer_digits_.size() != num.rev_integer_digits_.size()) {
    return this->rev_integer_digits_.size() > num.rev_integer_digits_.size()
               ? two_num_is_positive
               : !two_num_is_positive;
  }

  // When the digits' length and sign are all same,
  // judged the digit from the hightest to the lowest.
  for (size_t i = this->rev_integer_digits_.size() - 1; i >= 0; --i) {
    if (this->rev_integer_digits_[i] != num.rev_integer_digits_[i]) {
      return this->rev_integer_digits_[i] > num.rev_integer_digits_[i]
                 ? two_num_is_positive
                 : !two_num_is_positive;
    }
  }

  return false;
}

bool hight_precision::Num::operator==(const hight_precision::Num &num) const {
  return !(this->is_minus_ != num.is_minus_ ||
           this->rev_integer_digits_ != num.rev_integer_digits_);
}

bool hight_precision::Num::operator!=(const hight_precision::Num &num) const {
  return (this->is_minus_ != num.is_minus_ ||
          this->rev_integer_digits_ != num.rev_integer_digits_);
}

bool hight_precision::Num::operator>=(const hight_precision::Num &num) const {
  return operator>(num) || operator==(num);
}

bool hight_precision::Num::operator<(const hight_precision::Num &num) const {
  return !operator>(num) && !operator==(num);
}

bool hight_precision::Num::operator<=(const hight_precision::Num &num) const {
  return !operator>(num) || operator==(num);
}

// The Hight Precision Num in
// Plus(), Sub(), Multply() Divided() are all positive (x.is_minus = false;)

hight_precision::Num hight_precision::Num::Plus(
    const hight_precision::Num &num1, const hight_precision::Num &num2) {
  hight_precision::Num res;
  res.rev_integer_digits_.resize(0);  // If not, the all result will be multply
                                      // 10 (liked this -> 1 + 1 = 20)

  char carry_num = '\0';  // Used the char to save memory.

  const size_t n1_size = num1.rev_integer_digits_.size();
  const size_t n2_size = num2.rev_integer_digits_.size();
  const size_t max_size = std::max(n1_size, n2_size);

  for (size_t i = 0; i < max_size || carry_num != 0; ++i) {
    char digit1 = i < n1_size ? num1.rev_integer_digits_[i] : '0';
    char digit2 = i < n2_size ? num2.rev_integer_digits_[i] : '0';

    char operate_digit = (digit1 - '0') + (digit2 - '0') + carry_num;
    res.rev_integer_digits_.push_back((operate_digit % 10) + '0');
    carry_num = operate_digit / 10;
  }

  if (carry_num) res.rev_integer_digits_.push_back(carry_num + '0');

  return res;
}

// num1 > num2 are required.
hight_precision::Num hight_precision::Num::Sub(
    const hight_precision::Num &num1, const hight_precision::Num &num2) {
  hight_precision::Num res;
  res.rev_integer_digits_.resize(0);  // If not, the all result will be multply
                                      // 10 (liked this -> 3 - 1 = 20)

  char borrow = '\0';
  char operate_digit = '\0';

  size_t n1_size = num1.rev_integer_digits_.size();
  size_t n2_size = num2.rev_integer_digits_.size();
  size_t max_size = std::max(n1_size, n2_size);

  for (size_t i = 0; i < max_size; ++i) {
    char digit1 = i < n1_size ? num1.rev_integer_digits_[i] - '0' : 0;
    char digit2 = i < n2_size ? num2.rev_integer_digits_[i] - '0' : 0;

    operate_digit = digit1 - digit2 - borrow;
    borrow = 0;

    if (operate_digit < 0) {
      operate_digit += 10;
      borrow = 1;
    }

    res.rev_integer_digits_.push_back(operate_digit + '0');
  }

  // Removed extra zero after the numbers (liked this -> "0100" to "01")
  while (res.rev_integer_digits_.size() > 1 &&
         res.rev_integer_digits_.back() == '0') {
    res.rev_integer_digits_.pop_back();
  }

  return res;
}

// num1 ≠ 0 and num2 ≠ 0 are required.
hight_precision::Num hight_precision::Num::Multply(
    const hight_precision::Num &num1, const hight_precision::Num &num2) {
  hight_precision::Num res;
  res.rev_integer_digits_ = std::string(
      num1.rev_integer_digits_.size() + num2.rev_integer_digits_.size(), '\0');
  char operate_digit = '\0';
  size_t offset = 0;
  for (size_t i = 0; i < num1.rev_integer_digits_.size(); ++i) {
    for (size_t j = 0; j < num2.rev_integer_digits_.size(); ++j) {
      operate_digit = (num1.rev_integer_digits_[i] - '0') *
                      (num2.rev_integer_digits_[j] - '0');
      res.rev_integer_digits_[j + offset] += operate_digit;
      if (res.rev_integer_digits_[j + offset] > 9) {
        res.rev_integer_digits_[j + offset + 1] +=
            res.rev_integer_digits_[j + offset] / 10;
        res.rev_integer_digits_[j + offset] =
            res.rev_integer_digits_[j + offset] % 10;
      }
    }
    offset++;
  }
  std::transform(res.rev_integer_digits_.begin(), res.rev_integer_digits_.end(),
                 res.rev_integer_digits_.begin(),
                 [](auto digit) { return digit + '0'; });
  res.rev_integer_digits_ = res.rev_integer_digits_.substr(
      0, res.rev_integer_digits_.find_last_not_of("0") + 1);
  return res;
}

// num1 > num2 and num2, num1 != 0 are required.
// It will return a pair contained quotient and residue
// (all of them are HightPrecision Num).
std::pair<hight_precision::Num, hight_precision::Num>
hight_precision::Num::Divided(const hight_precision::Num &num1,
                              const hight_precision::Num &num2) {
  // res.first is the quotient
  // res.second is the residue
  std::pair<hight_precision::Num, hight_precision::Num> res = {
      hight_precision::Num(0), num1};
  res.first.rev_integer_digits_.resize(0, '\0');

  size_t supply_zero_num = 0;
  if (num1.rev_integer_digits_.size() == num2.rev_integer_digits_.size() + 1 &&
      num1.rev_integer_digits_.end() >= num2.rev_integer_digits_.end()) {
    // In this situation, let the divisor multply 10 can reduced the subtraction
    // times
    // like this -> 30 ÷ 3 the quotient's changed is from 0 to 30,
    // to 30 ÷ 30, the quotient's changed is from 0 to 10
    supply_zero_num = 1;
  } else if (num1.rev_integer_digits_.size() >
             num2.rev_integer_digits_.size()) {
    supply_zero_num =
        num1.rev_integer_digits_.size() - num2.rev_integer_digits_.size();
  }
  hight_precision::Num divisor_num = num2;

  // To reduced the operate times, multply some 10 to align the divisor
  // liked this ->
  // 320 ÷ 10, let 10 to 100.
  divisor_num.rev_integer_digits_.insert(
      divisor_num.rev_integer_digits_.begin(), supply_zero_num, '0');
  char quotient_digit;

  while (res.second >= num2) {
    quotient_digit = '\0';

    while (res.second >= divisor_num) {
      res.second -= divisor_num;
      quotient_digit++;
      if (quotient_digit > 9) {
        quotient_digit %= 10;
        res.first.rev_integer_digits_.push_back('0');
      }
    }
    res.first.rev_integer_digits_.push_back(quotient_digit + '0');
    if (supply_zero_num > 0) {
      divisor_num.rev_integer_digits_.erase(
          divisor_num.rev_integer_digits_.begin());
    } else {
      break;
    }
  }

  std::reverse(res.first.rev_integer_digits_.begin(),
               res.first.rev_integer_digits_.end());

  return res;
}

// Do as a common integer.
hight_precision::Num hight_precision::pow(const hight_precision::Num &num,
                                          const int &index) {
  if (index < 0) {
    throw std::invalid_argument(
        "Negative exponent not supported for high precision integers.");
  } else if (index == 0 || num == hight_precision::Num(1)) {
    return hight_precision::Num(1);
  } else if (num == hight_precision::Num(0)) {
    return hight_precision::Num(0);
  } else if (num == hight_precision::Num(-1)) {
    return index % 2 == 0 ? hight_precision::Num(1) : hight_precision::Num(-1);
  }

  hight_precision::Num base = num;
  int n = index;
  hight_precision::Num res(1);
  while (n > 0) {
    if (n & 1) {
      res *= base;
    }
    n >>= 1;
    if (n > 0) {
      base *= base;
    }
  }

  if (num.is_minus_ && (index % 2 != 0)) res.is_minus_ = true;

  return res;
}

// Do as a common integer.
hight_precision::Num hight_precision::abs(const hight_precision::Num &num) {
  if (!num.is_minus_) return num;
  hight_precision::Num res = num;
  res.is_minus_ = false;
  return res;
}

hight_precision::Num hight_precision::Num::operator+(
    const hight_precision::Num &num) {
  if (!(this->is_minus_) && !num.is_minus_) {
    return Plus(*this, num);
  } else if (this->is_minus_ && num.is_minus_) {
    hight_precision::Num res = Plus(abs(*this), abs(num));
    res.is_minus_ = (res.rev_integer_digits_ != "0") ? true : false;
    return res;
  }
  if (!this->is_minus_ && num.is_minus_) {
    return Sub(*this, abs(num));
  } else {
    return Sub(num, abs(*this));
  }
}

hight_precision::Num hight_precision::Num::operator-(
    const hight_precision::Num &num) {
  if (!(this->is_minus_) && !num.is_minus_) {
    if (*this >= num) {
      return Sub(*this, num);
    } else {
      hight_precision::Num res = Sub(num, *this);
      res.is_minus_ = true;
      return res;
    }
  } else if (this->is_minus_ && num.is_minus_) {
    if (*this >= num) {
      return Sub(abs(num), abs(*this));
    } else {
      hight_precision::Num res = Sub(abs(*this), abs(num));
      res.is_minus_ = true;
      return res;
    }
  }
  if (*this >= num) {
    return Plus(*this, abs(num));
  } else {
    hight_precision::Num res = Plus(abs(*this), abs(num));
    res.is_minus_ = true;
    return res;
  }
}

hight_precision::Num hight_precision::Num::operator-() {
  if (this->rev_integer_digits_ == "0") return *this;
  this->is_minus_ = !this->is_minus_;
  return *this;
}

hight_precision::Num hight_precision::Num::operator*(
    const hight_precision::Num &num) {
  if (num != hight_precision::Num(0) && *this != hight_precision::Num(0)) {
    if (num.is_minus_ == this->is_minus_) {
      return Multply(abs(*this), abs(num));
    } else {
      hight_precision::Num res = Multply(abs(*this), abs(num));
      res.is_minus_ = true;
      return res;
    }
  } else {
    return hight_precision::Num(0);
  }
  return hight_precision::Num(-1);
}

hight_precision::Num hight_precision::Num::operator/(
    const hight_precision::Num &num) {
  if (num == hight_precision::Num(0)) {
    throw std::invalid_argument("Division by zero");
  }
  if (*this == hight_precision::Num(0) || *this < num) {
    return hight_precision::Num(0);
  }
  if (*this == num) return hight_precision::Num(1);
  hight_precision::Num res = Divided(abs(*this), abs(num)).first;
  res.is_minus_ = this->is_minus_ ^ num < 0;
  return res;
}

hight_precision::Num hight_precision::Num::operator%(
    const hight_precision::Num &num) {
  if (num == hight_precision::Num(0)) {
    throw std::invalid_argument("Division by zero");
  }
  if (*this == hight_precision::Num(0) || *this == num) {
    return hight_precision::Num(0);
  }
  if (*this < num) return *this;
  hight_precision::Num res = Divided(abs(*this), abs(num)).second;
  res.is_minus_ = this->is_minus_;
  return res;
}

hight_precision::Num &&hight_precision::Num::operator++() {
  *this = operator+(hight_precision::Num(1));
  return *this;
}

hight_precision::Num hight_precision::Num::operator++(int) {
  hight_precision::Num res = *this;
  *this = operator+(hight_precision::Num(1));
  return res;
}

hight_precision::Num &&hight_precision::Num::operator--() {
  *this = operator-(hight_precision::Num(1));
  return *this;
}

hight_precision::Num hight_precision::Num::operator--(int) {
  hight_precision::Num res = *this;
  *this = operator-(hight_precision::Num(1));
  return res;
}

void hight_precision::Num::operator+=(const hight_precision::Num &num) {
  *this = this->operator+(num);
}

void hight_precision::Num::operator-=(const hight_precision::Num &num) {
  *this = this->operator-(num);
}

void hight_precision::Num::operator*=(const hight_precision::Num &num) {
  *this = this->operator*(num);
}

void hight_precision::Num::operator/=(const hight_precision::Num &num) {
  *this = this->operator/(num);
}

void hight_precision::Num::operator%=(const hight_precision::Num &num) {
  *this = this->operator%(num);
}

#endif  // HP_INT_H_
