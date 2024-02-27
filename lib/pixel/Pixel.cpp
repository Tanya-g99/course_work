#include "Pixel.hpp"

Pixel::Pixel() {
    x_ = 0;
    y_ = 0;
}

Pixel::Pixel(int x, int y) {
    x_ = x;
    y_ = y;
    color_ = Color(0, 0, 0);
}

Pixel::Pixel(int x, int y, int c) {
    x_ = x;
    y_ = y;
    color_ = Color(c, c, c);
}

Pixel::Pixel(int x, int y, Color color) {
    x_ = x;
    y_ = y;
    color_ = color;
}

void Pixel::set_x(int x) {
    x_ = x;
}

void Pixel::set_y(int y) {
    y_ = y;
}

void Pixel::set_color(Color color) {
    color_ = color;
}

void Pixel::set(int x, int y) {
    x_ = x;
    y_ = y;
}

int Pixel::get_x() const {
    return x_;
}

int Pixel::get_y() const {
    return y_;
}

Color Pixel::get_color() const {
    return color_;
}

bool Pixel::operator==(const Pixel &obj) const {
    return x_ == obj.x_ && y_ == obj.y_;
}

float Pixel::get_brightness() const {
    return 1 - (color_.b + color_.g + color_.r) / (float)(255 * 3);
}

float Pixel::get_dif(const Pixel &obj) const {
    return 1. - ((abs(color_.b - obj.get_color().b) + abs(color_.g - obj.get_color().g) +
                  abs(color_.r - obj.get_color().r)) /
                 (255 * 3));
}

bool Pixel::operator<(const Pixel &obj) const {
    return x_ < obj.x_ || (x_ == obj.x_ && y_ < obj.y_);
}

bool Pixel::operator>(const Pixel &obj) const {
    return obj < *this;
}

std::ostream &operator<<(std::ostream &os, const Pixel &obj) {
    return os << "Pixel(" << obj.get_x() << ", " << obj.get_y() << ")";
}
