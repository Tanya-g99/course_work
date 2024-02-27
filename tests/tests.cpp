#include <gtest/gtest.h>
#include "test.hpp"

TEST_F(UnitTests_long_int, NaiveAlgorithmTest) {
    run_tests(naive_algorithm, &UnitTests_long_int::CHECK_NOT_DIFFERENCE);
}

TEST_F(UnitTests_long_int, DifferentialAnalyzerTest) {
    run_tests(digital_differential_analyzer, &UnitTests_long_int::CHECK_NOT_DIFFERENCE, {test6, test11});
}

TEST_F(UnitTests_long_int, BresenhamFloatTest) {
    run_tests(bresenham_float, &UnitTests_long_int::CHECK_NOT_DIFFERENCE);
}

TEST_F(UnitTests_long_int, BresenhamIntegerTest) {
    run_tests(bresenham_integer, &UnitTests_long_int::CHECK_NOT_DIFFERENCE);
}

TEST_F(UnitTests_long_int, MidPointTest) {
    run_tests(mid_point, &UnitTests_long_int::CHECK_NOT_DIFFERENCE);
}

TEST_F(UnitTests_long_int, GuptaSproullAlgorithmTest) {
    run_tests(Gupta_Sproull_algorithm, &UnitTests_long_int::CHECK_ABSORPTION);
}

TEST_F(UnitTests_long_int, XiaolinWuAlgorithmTest) {
    run_tests(Xiaolin_Wu_algorithm, &UnitTests_long_int::CHECK_ABSORPTION);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
