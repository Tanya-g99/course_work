#include <gtest/gtest.h>
#include "test.hpp"

TEST_F(UnitTests_long_int, NaiveAlgorithmTest) {
    run_brightness_tests(naive_algorithm);
}

TEST_F(UnitTests_long_int, DifferentialAnalyzerTest) {
    run_brightness_tests(digital_differential_analyzer);
}

TEST_F(UnitTests_long_int, BresenhamFloatTest) {
    run_brightness_tests(bresenham_float);
}

TEST_F(UnitTests_long_int, BresenhamIntegerTest) {
    run_brightness_tests(bresenham_integer);
}

TEST_F(UnitTests_long_int, MidPointTest) {
    run_brightness_tests(mid_point);
}

TEST_F(UnitTests_long_int, GuptaSproullAlgorithmTest) {
    run_brightness_tests(Gupta_Sproull_algorithm, {test1, test2, test3, test4, test5, test6, test7, test9, test10, test11, test12});
}

TEST_F(UnitTests_long_int, XiaolinWuAlgorithmTest) {
    run_brightness_tests(Xiaolin_Wu_algorithm);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
