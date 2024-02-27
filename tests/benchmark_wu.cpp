#include <benchmark/benchmark.h>

#include "benchmark.hpp"

BENCHMARK_DEFINE_F(MyFixture, XiaolinWuAlgorithmBTest)(benchmark::State& st) {
    for (auto _ : st) {
        Xiaolin_Wu_algorithm(begin, end, &points);
        benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_TESTS(XiaolinWuAlgorithmBTest);

BENCHMARK_MAIN();
