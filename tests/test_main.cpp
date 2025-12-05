#include "Timer.hpp"
#include <cassert>

int main() {
    {
        Timer timer1{};
        Timer timer2{};
        constexpr auto milisecond = Timer::milliseconds_t(1);
        constexpr int repeteations = 10000;
        Timer::milliseconds_t actual_time{};
        timer1.tic();
        for (int i{0}; i < repeteations; ++i) {
            timer2.reset();
            while (timer2.is_time_remaining(milisecond)) {
                // wait...
            }
            actual_time += timer2.elapsed();
        }
        auto duration = timer1.elapsed();
        assert(duration > actual_time);
        assert(duration < (actual_time + milisecond));
    }
    return 0;
}
