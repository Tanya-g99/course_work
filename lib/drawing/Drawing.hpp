#pragma once

#include "Pixel.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Display {
  private:
    int width_, height_, block_size_;
    cv::Mat img_;

    void draw_single_pixel(Pixel p);

  public:
    Display(int width, int height, int block_size);
    void draw_pixels(std::vector<Pixel> points);
    void create_file(std::string folder_name, std::string file_name);
};
