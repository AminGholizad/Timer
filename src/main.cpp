#include "timer.hpp"

int main()
{
    Timer t{};
    t.tic();
    for (int i{0}; i < 1000000; ++i)
        int x = 10 * 10;
    t.toc();
    return 0;
}