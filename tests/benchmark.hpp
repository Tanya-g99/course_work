#include <benchmark/benchmark.h>

#include "Pixel.hpp"
#include "Algorithms.hpp"
#include "data.hpp"

class MyFixture : public benchmark::Fixture {
  public:
    void SetUp(::benchmark::State& state) {
        begin = std::make_pair(state.range(0), state.range(1));
        end = std::make_pair(state.range(2), state.range(3));
        benchmark::DoNotOptimize(points);
    }

    void TearDown(::benchmark::State& state) {}

    std::pair<float, float> begin;
    std::pair<float, float> end;
    std::vector<Pixel> points;
};

#define BENCHMARK_REGISTER_TESTS(Method)    \
    BENCHMARK_REGISTER_F(MyFixture, Method) \
        ->Args(test1.data)                  \
        ->Args(test4.data)                  \
        ->Args(test5.data)                  \
        ->Args(test6.data)                  \
        ->Args(test8.data)                  \
        ->Args(test11.data)                 \
        ->Args(test13.data);
