#include <benchmark/benchmark.h>

#include "benchmark.hpp"

BENCHMARK_DEFINE_F(MyFixture, NaiveAlgorithmBTest)(benchmark::State& st) {
    for (auto _ : st) {
        naive_algorithm(begin, end, &points);
        benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_TESTS(NaiveAlgorithmBTest);

BENCHMARK_MAIN();
