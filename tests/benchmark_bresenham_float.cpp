#include <benchmark/benchmark.h>

#include "benchmark.hpp"

BENCHMARK_DEFINE_F(MyFixture, BresenhamFloatBTest)(benchmark::State& st) {
    for (auto _ : st) {
        bresenham_float(begin, end, &points);
        benchmark::ClobberMemory();
    }
}
BENCHMARK_REGISTER_TESTS(BresenhamFloatBTest);

BENCHMARK_MAIN();
