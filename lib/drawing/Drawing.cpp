#include <iostream>
#include <vector>

#include "Drawing.hpp"
#include "Pixel.hpp"

Display::Display(int width, int height, int block_size) :
    width_(width),
    height_(height),
    block_size_(block_size),
    img_(height, width, CV_8UC3, cv::Scalar(255, 255, 255)) {
    if (block_size_ > 10) {
        for (int x = 0; x < width_; x++) {
            for (int y = 0; y < height_ / 2; y += block_size_) {
                cv::Rect rect(x, height_ / 2 + y, 1, 1);
                cv::Rect rect2(x, height_ / 2 - y, 1, 1);
                cv::Scalar blockColor = cv::Scalar(200, 200, 255);
                cv::rectangle(img_, rect, blockColor);
                cv::rectangle(img_, rect2, blockColor);
            }
        }

        for (int x = 0; x < width_ / 2; x += block_size_) {
            for (int y = 0; y < height_; y++) {
                cv::Rect rect(width_ / 2 + x, y, 1, 1);
                cv::Rect rect2(width_ / 2 - x, y, 1, 1);
                cv::Scalar blockColor = cv::Scalar(200, 200, 255);
                cv::rectangle(img_, rect, blockColor);
                cv::rectangle(img_, rect2, blockColor);
            }
        }
    }
    for (int x = 0; x < width_; x++) {
        cv::Rect rect(x, (height_ + block_size_) / 2, 1, 1);
        cv::Scalar blockColor = cv::Scalar(0, 0, 255);
        cv::rectangle(img_, rect, blockColor);
    }
    for (int y = 0; y < height_; y++) {
        cv::Rect rect((width_ + block_size_) / 2, y, 1, 1);
        cv::Scalar blockColor = cv::Scalar(0, 0, 255);
        cv::rectangle(img_, rect, blockColor);
    }
}

void Display::draw_single_pixel(Pixel p) {
    cv::Rect rect((width_ / 2) + (p.get_x()) * block_size_,
                  (height_ / 2) + (p.get_y()) * block_size_, block_size_, block_size_);
    cv::Scalar blockColor = cv::Scalar(p.get_color().b, p.get_color().g, p.get_color().r);
    cv::rectangle(img_, rect, blockColor, cv::FILLED);
}

void Display::draw_pixels(std::vector<Pixel> points) {
    for (Pixel p : points) {
        draw_single_pixel(p);
    }
}

void Display::create_file(std::string folder_name, std::string file_name) {
    cv::flip(img_, img_, 0);
    if (cv::imwrite(
            "/home/gnatenkota/vsc/course_work/tests/" + folder_name + "/" + file_name + ".png",
            img_))
        std::cout << "Сохранено в " << file_name + ".png" << std::endl;
    else
        std::cout << "Ошибка сохранения в " << file_name + ".png" << std::endl;
}
