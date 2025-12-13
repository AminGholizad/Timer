#ifndef TIMER_HPP
#define TIMER_HPP
#pragma once
#include <chrono>
#include <iostream>
namespace Timer {
constexpr size_t THOUSAND = 1000ULL;
using clock_t = std::chrono::steady_clock;
using milliseconds_t = std::chrono::duration<double, std::ratio<1, THOUSAND>>;
using time_t = std::chrono::time_point<clock_t>;
constexpr milliseconds_t MICRO = milliseconds_t(1e-3);

class Timer {

  public:
    void reset() { m_start = clock_t::now(); }

    [[nodiscard]] milliseconds_t elapsed() const { return clock_t::now() - m_start; }
    [[nodiscard]] bool is_time_remaining(milliseconds_t duration) const {
        return (duration - elapsed()) > MICRO;
    }
    void tic() { reset(); }
    void toc() const {
        auto elapsed_time{elapsed()};
        std::cout << "It took " << elapsed_time << "ms to run\n";
    }

  private:
    time_t m_start{clock_t::now()};
};
} // namespace Timer
#endif // !TIMER_HPP
