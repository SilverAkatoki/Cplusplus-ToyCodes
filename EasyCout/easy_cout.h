
#if __cplusplus >= 200704L

#ifndef CPLUSPLUSTOYSCODE_EASYCOUT_EASY_COUT_H_
#define CPLUSPLUSTOYSCODE_EASYCOUT_EASY_COUT_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& output_vector);

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& output_pair);

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const T (&output_array)[N]);

template <typename Key, typename Value>
std::ostream& operator<<(
    std::ostream& os,
    const std::unordered_map<Key, Value>& output_unordered_map);

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os,
                         const std::map<Key, Value>& output_map);

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T> output_set);

template <typename T>
std::ostream& operator<<(std::ostream& os,
                         const std::unordered_set<T> output_unordered_set);

/* -------------------------------------------------------------------------- */

template <typename T>
void Print(std::ostream& os, const T& basic_type_item);

template <typename T>
void Print(std::ostream& os, const std::vector<T>& vector_item);

template <typename T, typename U>
void Print(std::ostream& os, const std::pair<T, U>& pair_item);

template <typename T, std::size_t N>
void Print(std::ostream& os, const T (&output_array)[N]);

template <typename Key, typename Value>
void Print(std::ostream& os,
           const std::unordered_map<Key, Value>& output_unordered_map);

template <typename Key, typename Value>
void Print(std::ostream& os, const std::map<Key, Value>& output_map);

template <typename Key, typename Value>
void Print(std::ostream& os, const std::map<Key, Value>& output_map);

template <typename T>
void Print(std::ostream& os, const std::unordered_set<T>& output_unordered_set);

/* -------------------------------------------------------------------------- */

// T
template <typename T>
void Print(std::ostream& os, const T& basic_type_item) {
  os << basic_type_item;
}

// std::vector<T>
template <typename T>
void Print(std::ostream& os, const std::vector<T>& vector_item) {
  if (vector_item.size() == 0) os << '{' << '}';
  os << '{';
  // std::copy(vector_item.begin(), vector_item.end(),
  //           std::ostream_iterator<U>(os, ", "));
  std::for_each(vector_item.begin(), vector_item.end(), [&os](T item) {
    Print(os, item);
    os << ',' << ' ';
  });
  os << '\b' << '\b' << '}';
}

// std::pair<T, U>
template <typename T, typename U>
void Print(std::ostream& os, const std::pair<T, U>& pair_item) {
  os << '{';
  Print(os, pair_item.first);
  os << ',' << ' ';
  Print(os, pair_item.second);
  os << '}';
}

// T[]
template <typename T, std::size_t N>
void Print(std::ostream& os, const T (&output_array)[N]) {
  size_t array_length = sizeof(output_array) / sizeof(output_array[0]);
  if (array_length == 0) os << '{' << '}';
  os << '{';
  std::for_each(output_array, output_array + array_length, [&os](T item) {
    Print(os, item);
    os << ',' << ' ';
  });
  os << '\b' << '\b' << '}';
}

// std::unordered_map<Key, Value>
template <typename Key, typename Value>
void Print(std::ostream& os,
           const std::unordered_map<Key, Value>& output_unordered_map) {
  if (output_unordered_map.size() == 0) os << '{' << '}';
  os << '{';
  for (std::pair<Key, Value>&& kv : output_unordered_map) {
    os << '{';
    Print(os, kv.first);
    os << ',' << ' ';
    Print(os, kv.second);
    os << '}' << ',' << ' ';
  }
  os << '\b' << '\b' << '}';
}

// std::map<Key, Value>
template <typename Key, typename Value>
void Print(std::ostream& os, const std::map<Key, Value>& output_map) {
  if (output_map.size() == 0) os << '{' << '}';
  os << '{';
  for (std::pair<Key, Value>&& kv : output_map) {
    os << '{';
    Print(os, kv.first);
    os << ',' << ' ';
    Print(os, kv.second);
    os << '}' << ',' << ' ';
  }
  os << '\b' << '\b' << '}';
}

// std::set<T>
template <typename T>
void Print(std::ostream& os, const std::set<T>& output_set) {
  if (output_set.size() == 0) os << '{' << '}';
  os << '{';
  std::for_each(output_set.begin(), output_set.end(), [&os](T item) {
    Print(os, item);
    os << ',' << ' ';
  });
  os << '\b' << '\b' << '}';
}

// std::unordered_set<T>
template <typename T>
void Print(std::ostream& os,
           const std::unordered_set<T>& output_unordered_set) {
  if (output_unordered_set.size() == 0) os << '{' << '}';
  os << '{';
  std::for_each(output_unordered_set.begin(), output_unordered_set.end(),
                [&os](T item) {
                  Print(os, item);
                  os << ',' << ' ';
                });
  os << '\b' << '\b' << '}';
}

/* -------------------------------------------------------------------------- */

template <typename T>
std::ostream& operator<<(std::ostream& os,
                         const std::vector<T>& output_vector) {
  Print(os, output_vector);
  return os;
}

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& output_pair) {
  Print(os, output_pair);
  return os;
}

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const T (&output_array)[N]) {
  Print(os, output_array);
  return os;
}

template <typename Key, typename Value>
std::ostream& operator<<(
    std::ostream& os,
    const std::unordered_map<Key, Value>& output_unordered_map) {
  Print(os, output_unordered_map);
  return os;
}

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os,
                         const std::map<Key, Value>& output_map) {
  Print(os, output_map);
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T> output_set) {
  Print(os, output_set);
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os,
                         const std::unordered_set<T> output_unordered_set) {
  Print(os, output_unordered_set);
  return os;
}

#endif  // CPLUSPLUSTOYSCODE_EASYCOUT_EASY_COUT_H_

#endif  // NOLINT
