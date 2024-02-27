#include <gtest/gtest.h>
#include "test.hpp"

TEST_F(UnitTests_float, NaiveAlgorithmTest) {
    run_float_tests(naive_algorithm, &UnitTests_float::CHECK_NOT_DIFFERENCE);
}

TEST_F(UnitTests_float, DifferentialAnalyzerTest) {
    run_float_tests(digital_differential_analyzer, &UnitTests_float::CHECK_NOT_DIFFERENCE);
}

TEST_F(UnitTests_float, BresenhamFloatTest) {
    run_float_tests(bresenham_float, &UnitTests_float::CHECK_NOT_DIFFERENCE,
                    {test21, test22, test23, test24, test25});
}

TEST_F(UnitTests_float, BresenhamIntegerTest) {
    run_float_tests(bresenham_integer, &UnitTests_float::CHECK_NOT_DIFFERENCE,
                    {test21, test22, test23, test24});
}

TEST_F(UnitTests_float, MidPointTest) {
    run_float_tests(mid_point, &UnitTests_float::CHECK_NOT_DIFFERENCE,
                    {test21, test22, test23, test24});
}

TEST_F(UnitTests_float, GuptaSproullAlgorithmTest) {
    run_float_tests(Gupta_Sproull_algorithm, &UnitTests_float::CHECK_ABSORPTION,
                    {test21, test22, test23, test24});
}

TEST_F(UnitTests_float, XiaolinWuAlgorithmTest) {
    run_float_tests(Xiaolin_Wu_algorithm, &UnitTests_float::CHECK_ABSORPTION);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
