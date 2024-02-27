#include <benchmark/benchmark.h>

#include "benchmark.hpp"

BENCHMARK_DEFINE_F(MyFixture, BresenhamIntegerBTest)(benchmark::State& st) {
    for (auto _ : st) {
        bresenham_integer(begin, end, &points);
        benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_TESTS(BresenhamIntegerBTest);

BENCHMARK_MAIN();
