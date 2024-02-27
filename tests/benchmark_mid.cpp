#include <benchmark/benchmark.h>

#include "benchmark.hpp"

BENCHMARK_DEFINE_F(MyFixture, MidPointBTest)(benchmark::State& st) {
    for (auto _ : st) {
        mid_point(begin, end, &points);
        benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_TESTS(MidPointBTest);

BENCHMARK_MAIN();
