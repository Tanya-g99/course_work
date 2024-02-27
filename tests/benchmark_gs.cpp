#include <benchmark/benchmark.h>

#include "benchmark.hpp"

BENCHMARK_DEFINE_F(MyFixture, GuptaSproullAlgorithmBTest)(benchmark::State& st) {
    for (auto _ : st) {
        Gupta_Sproull_algorithm(begin, end, &points);
        benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_TESTS(GuptaSproullAlgorithmBTest);

BENCHMARK_MAIN();
