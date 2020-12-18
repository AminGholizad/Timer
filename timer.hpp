#ifndef TIMER_HPP
#define TIMER_HPP
#pragma once
#include <chrono>
#include <iostream>

class Timer
{
private:
    using clock_t = std::chrono::steady_clock;
    using milliseconds_t = std::chrono::duration<double, std::ratio<1, 1000>>;
    using time_t = std::chrono::time_point<clock_t>;

    std::chrono::time_point<clock_t> m_start{clock_t::now()};

public:
    Timer() : m_start{clock_t::now()}
    {
    }

    void reset() { m_start = clock_t::now(); }

    double elapsed() const
    {
        return milliseconds_t(clock_t::now() - m_start).count();
    }
    bool is_time_remaining(double d)
    {
        return (elapsed() - d) > 1e-3;
    }
    void tic() { reset(); }
    void toc()
    {
        auto elapsed_time{elapsed()};
        std::cout << "It took " << elapsed_time << "ms to run\n";
    }
};
#endif // !TIMER_HPP