#include <gtest/gtest.h>

#include "Pixel.hpp"
#include "Algorithms.hpp"
#include "Drawing.hpp"
#include "data.hpp"
#include <algorithm>
#include <cmath>

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& v) {
    os << '{';
    for (auto n{v.size()}; T const& e : v) os << e << (--n ? ", " : "");
    return os << "}\n";
}

template <typename DataType>
class UnitTests : public testing::Test {
  public:
    void run_brightness_tests(void (*algorithm)(std::pair<float, float> begin,
                                                std::pair<float, float> end,
                                                std::vector<Pixel>* ps),
                              std::vector<TestData<DataType>> falling_tests = {}) {
        for (test_number = 1; TestData<DataType> const& test : tests) {
            init_points(test.data);
            algorithm(begin, end, &points);
            std::vector<Pixel> standard;
            float len = hypot(begin.first - end.first, begin.second - end.second);
            std::pair<float, float> standard_end =
                std::make_pair(begin.first, begin.second + floor(len));
            algorithm(begin, standard_end, &standard);

            float pb = get_brightness_line(points, begin, end);
            float sb = get_brightness_line(standard, begin, standard_end);

            std::cout << "Test" << test_number << "(" << test.name << "): ";
            analyze_brightness(
                pb, sb,
                std::find(falling_tests.begin(), falling_tests.end(), test) != falling_tests.end());
            test_number++;
        }
    }
    void run_tests(void (*algorithm)(std::pair<float, float> begin, std::pair<float, float> end,
                                     std::vector<Pixel>* ps),
                   void (UnitTests::*expectence_fun)(std::vector<Pixel>, std::vector<Pixel>, bool),
                   std::vector<TestData<DataType>> falling_tests = {}) {
        for (test_number = 1; auto const& test : tests) {
            init_points(test.data);
            algorithm(begin, end, &points);
            (this->*expectence_fun)(
                points, test.result,
                std::find(falling_tests.begin(), falling_tests.end(), test) != falling_tests.end());
            create_picture();
            test_number++;
        }
    }

    void run_float_tests(void (*algorithm)(std::pair<float, float> begin,
                                           std::pair<float, float> end, std::vector<Pixel>* ps),
                         void (UnitTests::*expectence_fun)(std::vector<Pixel>, std::vector<Pixel>,
                                                           bool),
                         std::vector<TestData<DataType>> falling_tests = {}) {
        for (test_number = 1; auto const& test : float_tests) {
            init_points(test.data);
            algorithm(begin, end, &points);
            (this->*expectence_fun)(
                points, test.result,
                std::find(falling_tests.begin(), falling_tests.end(), test) != falling_tests.end());
            create_picture();
            test_number++;
        }
    }

    void init_points(std::vector<DataType> data) {
        begin = std::make_pair(data[0], data[1]);
        end = std::make_pair(data[2], data[3]);
        points = {};
    }

    void create_picture() {
        int n = int(std::max(std::max(abs(begin.first), abs(end.first)),
                             std::max(abs(begin.second), abs(end.second)))) +
                1;
        auto size = std::max(800, n * 2);
        auto block_size = std::floor(size / (float)(2 * n));
        auto d = Display(size + 2 * block_size, size + 2 * block_size, block_size);
        d.draw_pixels(points);
        std::string type = typeid(DataType).name();
        d.create_file("pic_" + type, testing::UnitTest::GetInstance()->current_test_info()->name() +
                                         std::to_string(test_number));
    }

    float get_brightness_line(std::vector<Pixel> line, std::pair<float, float> begin,
                              std::pair<float, float> end) {
        float brightness = 0;
        for (auto p : line) {
            brightness += p.get_brightness();
        }
        float len = hypot(begin.first - end.first, begin.second - end.second);
        float brightness_coef = (brightness - line[0].get_brightness()) / len;
        return brightness_coef;
    }

    void analyze_brightness(float line_brightness, float standard_brightness, bool expect_fail) {
        float brightness_coef = line_brightness / standard_brightness;
        std::cout << "brightness coefficient: " << brightness_coef;
        if (expect_fail) {
            EXPECT_FALSE(brightness_coef <= 1);
            std::cout << "(more than 1)";
        } else
            EXPECT_TRUE(brightness_coef <= 1);
        std::cout << std::endl;
    }

    float analyze_dif_brightness(std::vector<Pixel> received, std::vector<Pixel> standard) {
        std::sort(received.begin(), received.end());
        std::sort(standard.begin(), standard.end());
        float brightness_max = 0;
        float brightness = 0;
        auto i = received.begin(), j = standard.begin();
        while (i != received.end() && j != standard.end()) {
            if (*i == *j) {
                brightness += (*i).get_dif(*j);
                i++;
                j++;
            } else if (*i > *j) {  // j -> Pixels are not filled
                j++;
            } else {  // i -> he extra pixels are filled
                i++;
            }

            brightness_max++;
        }
        for (; i != received.end(); i++) {
            brightness_max++;
        }
        for (; j != standard.end(); j++) {
            brightness_max++;
        }
        float brightness_coef = 0;
        if (brightness_max != 0) {
            brightness_coef = brightness / brightness_max;
        }
        EXPECT_TRUE(brightness_coef <= 1);
        return brightness_coef;
    }

    // включение полученного в ожидаемое
    std::vector<Pixel> inclusion(std::vector<Pixel> received, std::vector<Pixel> expected) {
        std::vector<Pixel> diff = {};
        std::sort(received.begin(), received.end());
        std::sort(expected.begin(), expected.end());
        std::set_difference(received.begin(), received.end(), expected.begin(), expected.end(),
                            std::back_inserter(diff));
        return diff;
    }
    void CHECK_INCLUSION(std::vector<Pixel> received, std::vector<Pixel> expected,
                         bool expect_fail) {
        std::vector<Pixel> diff = inclusion(received, expected);
        if (expect_fail) {
            EXPECT_FALSE(diff.empty());
            std::cout << "Test" << test_number << ":\n"
                      << "The extra pixels are filled:" << diff;
        } else {
            EXPECT_TRUE(diff.empty()) << "Test" << test_number << ":\n"
                                      << "The extra pixels are filled:" << diff;
        }
    }

    // поглощение полученным ожидаемого
    std::vector<Pixel> absorption(std::vector<Pixel> received, std::vector<Pixel> expected) {
        std::vector<Pixel> diff = {};
        std::sort(received.begin(), received.end());
        std::sort(expected.begin(), expected.end());
        std::set_difference(expected.begin(), expected.end(), received.begin(), received.end(),
                            std::back_inserter(diff));
        return diff;
    }
    void CHECK_ABSORPTION(std::vector<Pixel> received, std::vector<Pixel> expected,
                          bool expect_fail) {
        std::vector<Pixel> diff = absorption(received, expected);
        if (expect_fail) {
            EXPECT_FALSE(diff.empty());
            std::cout << "Test" << test_number << ":\n"
                      << "Pixels are not filled: " << diff;
        } else {
            EXPECT_TRUE(diff.empty()) << "Test" << test_number << ":\n"
                                      << "Pixels are not filled: " << diff;
        }
    }

    void CHECK_NOT_DIFFERENCE(std::vector<Pixel> received, std::vector<Pixel> expected,
                              bool expect_fail) {
        std::vector<Pixel> inclusion_diff = inclusion(received, expected);
        std::vector<Pixel> absorption_diff = absorption(received, expected);
        if (expect_fail) {
            EXPECT_FALSE(inclusion_diff.empty() && absorption_diff.empty());
            if (!inclusion_diff.empty())
                std::cout << "Test" << test_number << ":\n"
                          << "The extra pixels are filled: " << inclusion_diff;
            if (!absorption_diff.empty())
                std::cout << "Test" << test_number << ":\n"
                          << "Pixels are not filled: " << absorption_diff;
        } else {
            EXPECT_TRUE(inclusion_diff.empty())
                << "Test" << test_number << ":\n"
                << "The extra pixels are filled:" << inclusion_diff << "\n"
                << received << "\n"
                << expected;
            EXPECT_TRUE(absorption_diff.empty()) << "Test" << test_number << ":\n"
                                                 << "Pixels are not filled: " << absorption_diff;
        }
    }

    std::string printPoints() {
        std::cout << "Test" << test_number << ":\n";

        std::cout << "Points:\n";
        for (auto p : points) {
            std::cout << "(" << p.get_x() << ", " << p.get_y() << ")\n";
        }

        std::cout << "Expected result:\n";
        for (auto p : tests[test_number - 1].result) {
            std::cout << "(" << p.get_x() << ", " << p.get_y() << ")\n";
        }
        return "";
    }

    std::string printColorPoints() {
        std::cout << "Test" << test_number + 1 << ":\n";

        std::cout << "Points:\n";
        for (auto p : points) {
            std::cout << "(" << p.get_x() << ", " << p.get_y() << ")  " << p.get_color()
                      << std::endl;
        }

        std::cout << "Expected result:\n";
        for (auto p : tests[test_number - 1].result) {
            std::cout << "(" << p.get_x() << ", " << p.get_y() << ")  " << p.get_color()
                      << std::endl;
        }
        return "";
    }

    std::pair<float, float> begin;
    std::pair<float, float> end;
    std::vector<Pixel> points;
    int test_number;
};

using UnitTests_long_int = UnitTests<long int>;
using UnitTests_float = UnitTests<float>;
