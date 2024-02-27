#include <benchmark/benchmark.h>

#include "benchmark.hpp"

BENCHMARK_DEFINE_F(MyFixture, DifferentialAnalyzerBTest)(benchmark::State& st) {
    for (auto _ : st) {
        digital_differential_analyzer(begin, end, &points);
        benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_TESTS(DifferentialAnalyzerBTest);

BENCHMARK_MAIN();
