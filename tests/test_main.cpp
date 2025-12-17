#include <Timer.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("waitng == counting") {
    Timer::Timer timer1{};
    Timer::Timer timer2{};
    constexpr int repeteations = 10000;
    constexpr Timer::milliseconds_t wait_time{1};
    Timer::milliseconds_t count_time{};
    timer1.tic();
    for (int i{0}; i < repeteations; ++i) {
        timer2.reset();
        while (timer2.is_time_remaining(wait_time)) {
            // wait...
        }
        count_time += timer2.elapsed();
    }
    auto duration = timer1.elapsed();
    REQUIRE(duration > count_time);
    REQUIRE(duration < (repeteations * wait_time));
    REQUIRE(duration > (repeteations * (wait_time - Timer::MICRO)));
}
