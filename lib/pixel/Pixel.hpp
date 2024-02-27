#pragma once
#include <iostream>

struct Color {
    int r, g, b;
    Color(int r, int g, int b) :
        r(r),
        g(g),
        b(b) {}
    Color() {}
    friend std::ostream &operator<<(std::ostream &os, Color const &color) {
        return os << "{" << color.r << ", " << color.g << ", " << color.b << "}";
    }
};

class Pixel {
  private:
    int x_, y_;
    Color color_;

  public:
    Pixel();
    Pixel(int x, int y);
    Pixel(int x, int y, int c);
    Pixel(int x, int y, Color color);

    void set_x(int x);
    void set_y(int y);
    void set_color(Color color);
    void set(int x, int y);

    int get_x() const;
    int get_y() const;
    Color get_color() const;

    float get_brightness() const;
    float get_dif(const Pixel &obj) const;
    
    bool operator==(const Pixel &obj) const;
    bool operator<(const Pixel &obj) const;
    bool operator>(const Pixel &obj) const;
    friend std::ostream &operator<<(std::ostream &os, const Pixel &obj);
};
