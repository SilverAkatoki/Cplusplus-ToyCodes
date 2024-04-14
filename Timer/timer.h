// Copyleft 2024 银晓 SilverAkatoki
// C++ 11 and after for the <chorono>

#if __cplusplus >= 200704L

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include <chrono>
#include <iostream>
#include <string>
#include <type_traits>

namespace timer {

typedef std::chrono::days d;
typedef std::chrono::hours h;
typedef std::chrono::minutes min;
typedef std::chrono::seconds sec;
typedef std::chrono::microseconds ms;
typedef std::chrono::milliseconds us;
typedef std::chrono::nanoseconds ns;

typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;

/********************************************
 * @brief A timer for any code pieces.
 * @tparam TimeUnit This must be one of the `timer::d`, `timer::h`,
 *`timer::min`, `timer::sec`, `timer::ms`, `timer::us`, `timer::ns`.
 *******************************************/
template <typename TimeUnit>
class Timer {
 public:
  Timer();
  inline void start();
  inline void end();
  inline void reset();
  inline std::string get();
  inline void paused();
  inline void continued();

 private:
  bool is_paused_;
  bool is_end_;
  TimePoint start_;
  TimePoint end_;
  TimeUnit interval_;
  const char* unit_;
};
}  // namespace timer

template <typename TimeUnit>
timer::Timer<TimeUnit>::Timer() {
  if constexpr (std::is_same_v<TimeUnit, timer::d>) {
    this->unit_ = "d";
  } else if constexpr (std::is_same_v<TimeUnit, timer::h>) {
    this->unit_ = "h";
  } else if constexpr (std::is_same_v<TimeUnit, timer::min>) {
    this->unit_ = "m";
  } else if constexpr (std::is_same_v<TimeUnit, timer::sec>) {
    this->unit_ = "s";
  } else if constexpr (std::is_same_v<TimeUnit, timer::ms>) {
    this->unit_ = "ms";
  } else if constexpr (std::is_same_v<TimeUnit, timer::us>) {
    this->unit_ = "us";
  } else if constexpr (std::is_same_v<TimeUnit, timer::ns>) {
    this->unit_ = "ns";
  }
  this->start_ = TimePoint();
  this->end_ = TimePoint();
  this->interval_ = TimeUnit();
  this->is_paused_ = false;
}

/************************
 * @brief Start the timer.
 ***********************/
template <typename TimeUnit>
void timer::Timer<TimeUnit>::start() {
  this->start_ = std::chrono::steady_clock::now();
}

/************************
 * @brief Stop the timer.
 ***********************/
template <typename TimeUnit>
void timer::Timer<TimeUnit>::end() {
  this->end_ = std::chrono::steady_clock::now();
  this->interval_ +=
      std::chrono::duration_cast<TimeUnit>(this->end_ - this->start_);
}

/*********************************************************
 * @brief Reset the timer without change the time unit.
 ********************************************************/
template <typename TimeUnit>
void timer::Timer<TimeUnit>::reset() {
  this->start_ = TimePoint();
  this->end_ = TimePoint();
  this->interval_ = TimeUnit();
}

/***************************************************************************
 * @brief Get the timer's result.
 * @return The formated string about the time data.( liked this: `"42ms"` )
 **************************************************************************/
template <typename TimeUnit>
std::string timer::Timer<TimeUnit>::get() {
  if (this->end_ == TimePoint()) {
    return std::to_string(std::chrono::duration_cast<TimeUnit>(
                              std::chrono::steady_clock::now() - this->start_)
                              .count())
        .append(this->unit_);
  } else {
    return std::to_string(this->interval_.count()).append(this->unit_);
  }
}

/******************************
 * @brief Paused the timer.
 *****************************/
template <typename TimeUnit>
void timer::Timer<TimeUnit>::paused() {
  if (this->is_paused_) {
    throw std::invalid_argument("Can't paused again.");
  }
  this->end_ = std::chrono::steady_clock::now();
  this->interval_ +=
      std::chrono::duration_cast<TimeUnit>(this->end_ - this->start_);
  this->start_ = TimePoint();
  this->is_paused_ = true;
}

/************************************************
 * @brief Continue after you paused the timer.
 ***********************************************/
template <typename TimeUnit>
void timer::Timer<TimeUnit>::continued() {
  if (!this->is_paused_) {
    throw std::invalid_argument("Doesn't need continue.");
  }
  this->start_ = std::chrono::steady_clock::now();
  this->is_paused_ = false;
}

#endif  // TIMER_TIMER_H_

#endif  // TIMER_TIMER_H_
