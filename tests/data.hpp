#include <vector>
#include "Pixel.hpp"
#include <math.h>

template <typename DataType>
struct TestData {
    std::vector<DataType> data;
    std::vector<Pixel> result;
    std::string name;

    TestData(std::vector<DataType> d, std::vector<Pixel> r) :
        data(d),
        result(r),
        name(get_name()) {}

    TestData(std::vector<DataType> d, std::vector<Pixel> r, std::string n) :
        data(d),
        result(r),
        name(n + ": " + get_name()) {}

    std::string get_name() {
        return "(" + std::to_string(data[0]) + "; " + std::to_string(data[1]) + ") to (" +
               std::to_string(data[2]) + "; " + std::to_string(data[3]) + ")" + " angle: " +
               std::to_string(
                   int(atan((data[3] - data[1]) / (float)(data[2] - data[0])) * 180 / M_PI)) +
               "°";
    }

    bool operator==(const TestData<DataType> &obj) const {
        return data == obj.data && result == obj.result && name == obj.name;
    }
};

std::vector<Pixel> make_diagonal_result(int begin, int end) {
    std::vector<Pixel> res;
    if (begin < end) {
        for (size_t i = begin; i <= end; i++) {
            res.push_back(Pixel(i, i));
        }
    } else {
        for (size_t i = begin; i >= end; i--) {
            res.push_back(Pixel(i, i));
        }
    }
    return res;
}

TestData<long int> test1({1, 1, 4, 4}, make_diagonal_result(1, 4));
TestData<long int> test2({1, 1, 30, 30}, make_diagonal_result(1, 30));
TestData<long int> test3({4, 4, 1, 1}, make_diagonal_result(4, 1));
TestData<long int> test4({400, 400, 1, 1}, make_diagonal_result(400, 1));
TestData<long int> test5({4, 4, 1, -3}, {Pixel(4, 4), Pixel(4, 3), Pixel(3, 2), Pixel(3, 1),
                                         Pixel(2, 0), Pixel(2, -1), Pixel(1, -2), Pixel(1, -3)});
TestData<long int> test6({0, 0, 24, 4},
                         {Pixel(0, 0),  Pixel(1, 0),  Pixel(2, 0),  Pixel(3, 1),  Pixel(4, 1),
                          Pixel(5, 1),  Pixel(6, 1),  Pixel(7, 1),  Pixel(8, 1),  Pixel(9, 2),
                          Pixel(10, 2), Pixel(11, 2), Pixel(12, 2), Pixel(13, 2), Pixel(14, 2),
                          Pixel(15, 3), Pixel(16, 3), Pixel(17, 3), Pixel(18, 3), Pixel(19, 3),
                          Pixel(20, 3), Pixel(21, 4), Pixel(22, 4), Pixel(23, 4), Pixel(24, 4)});
TestData<long int> test7({-2, -1, -20, -10},
                         {Pixel(-2, -1), Pixel(-3, -2), Pixel(-4, -2), Pixel(-5, -3), Pixel(-6, -3),
                          Pixel(-7, -4), Pixel(-8, -4), Pixel(-9, -5), Pixel(-10, -5),
                          Pixel(-11, -6), Pixel(-12, -6), Pixel(-13, -7), Pixel(-14, -7),
                          Pixel(-15, -8), Pixel(-16, -8), Pixel(-17, -9), Pixel(-18, -9),
                          Pixel(-19, -10), Pixel(-20, -10)});
TestData<long int> test8({-2, -1, 10, -1},
                         {Pixel(-2, -1), Pixel(-1, -1), Pixel(0, -1), Pixel(1, -1), Pixel(2, -1),
                          Pixel(3, -1), Pixel(4, -1), Pixel(5, -1), Pixel(6, -1), Pixel(7, -1),
                          Pixel(8, -1), Pixel(9, -1), Pixel(10, -1)},
                         "horizontal line");
TestData<long int> test9({1, 4, 4, 1}, {Pixel(1, 4), Pixel(2, 3), Pixel(3, 2), Pixel(4, 1)});
TestData<long int> test10({0, 0, 3, 4},
                          {Pixel(0, 0), Pixel(1, 1), Pixel(2, 2), Pixel(2, 3), Pixel(3, 4)});
TestData<long int> test11({0, 0, 3, 28},
                          {Pixel(0, 0),  Pixel(0, 1),  Pixel(0, 2),  Pixel(0, 3),  Pixel(0, 4),
                           Pixel(1, 5),  Pixel(1, 6),  Pixel(1, 7),  Pixel(1, 8),  Pixel(1, 9),
                           Pixel(1, 10), Pixel(1, 11), Pixel(1, 12), Pixel(1, 13), Pixel(2, 14),
                           Pixel(2, 15), Pixel(2, 16), Pixel(2, 17), Pixel(2, 18), Pixel(2, 19),
                           Pixel(2, 20), Pixel(2, 21), Pixel(2, 22), Pixel(2, 23), Pixel(3, 24),
                           Pixel(3, 25), Pixel(3, 26), Pixel(3, 27), Pixel(3, 28)});

TestData<long int> test12({-2, 0, 4, -2}, {Pixel(-2, 0), Pixel(-1, 0), Pixel(0, -1), Pixel(1, -1),
                                           Pixel(2, -1), Pixel(3, -2), Pixel(4, -2)});
TestData<long int> test13({1, 1, 1, -9},
                          {Pixel(1, 1), Pixel(1, 0), Pixel(1, -1), Pixel(1, -2), Pixel(1, -3),
                           Pixel(1, -4), Pixel(1, -5), Pixel(1, -6), Pixel(1, -7), Pixel(1, -8),
                           Pixel(1, -9)},
                          "vertical line");

static std::vector<TestData<long int>> tests = {test1, test2, test3,  test4,  test5,  test6, test7,
                                                test8, test9, test10, test11, test12, test13};

TestData<float> test21({0.5, 0.5, 3.5, 3.5}, {Pixel(1, 1), Pixel(2, 2), Pixel(3, 3), Pixel(4, 4)});
TestData<float> test22({0.7, 0.7, 3.7, 3.7}, {Pixel(1, 1), Pixel(2, 2), Pixel(3, 3), Pixel(4, 4)});
TestData<float> test23({1.2, 4.2, 4.2, 1.2}, {Pixel(1, 4), Pixel(2, 3), Pixel(3, 2), Pixel(4, 1)});
TestData<float> test24({-1.8, 0.3, 4.2, -1.7},
                       {Pixel(-2, 0), Pixel(-1, 0), Pixel(0, 0), Pixel(1, -1), Pixel(2, -1),
                        Pixel(3, -1), Pixel(4, -2)});
TestData<float> test25({-2.4, -1.4, 10.4, -1.4},
                       {Pixel(-2, -1), Pixel(-1, -1), Pixel(0, -1), Pixel(1, -1), Pixel(2, -1),
                        Pixel(3, -1), Pixel(4, -1), Pixel(5, -1), Pixel(6, -1), Pixel(7, -1),
                        Pixel(8, -1), Pixel(9, -1), Pixel(10, -1)});

static std::vector<TestData<float>> float_tests = {test21, test22, test23, test24, test25};
