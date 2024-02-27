#include "Pixel.hpp"

#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>

// https://en.wikipedia.org/wiki/Line_drawing_algorithm
void naive_algorithm(std::pair<float, float> begin, std::pair<float, float> end,
                     std::vector<Pixel>* ps) {
    float dx = end.first - begin.first, dy = end.second - begin.second;

    if (abs(dx) >= abs(dy)) {
        if (begin.first < end.first) {
            for (float x = begin.first; x <= end.first; x++) {
                float y = round(begin.second + dy * (x - begin.first) / dx);
                (*ps).push_back(Pixel(round(x), round(y)));
            }
        } else {
            for (float x = begin.first; x >= end.first; x--) {
                float y = round(begin.second + dy * (x - begin.first) / dx);
                (*ps).push_back(Pixel(round(x), round(y)));
            }
        }
    } else {
        if (begin.second < end.second) {
            for (float y = begin.second; y <= end.second; y++) {
                float x = round(begin.first + dx * (y - begin.second) / dy);
                (*ps).push_back(Pixel(round(x), round(y)));
            }
        } else {
            for (float y = begin.second; y >= end.second; y--) {
                float x = round(begin.first + dx * (y - begin.second) / dy);
                (*ps).push_back(Pixel(round(x), round(y)));
            }
        }
    }
}

void digital_differential_analyzer(std::pair<float, float> begin, std::pair<float, float> end,
                                   std::vector<Pixel>* ps) {
    float n = std::max(abs(begin.first - end.first), abs(begin.second - end.second));

    float dx = end.first - begin.first, dy = end.second - begin.second;
    float x = begin.first, y = begin.second;

    float xinc = dx / (float)n;
    float yinc = dy / (float)n;

    for (float wid = 0.0; n + std::numeric_limits<float>::epsilon() * n >= wid; wid++) {
        (*ps).push_back(Pixel(round(x), round(y)));
        x += xinc;
        y += yinc;
    }
}

void bresenham_float(std::pair<float, float> begin, std::pair<float, float> end,
                     std::vector<Pixel>* ps) {
    float x = begin.first, dx = end.first - begin.first;
    float y = begin.second, dy = end.second - begin.second;
    int sign_x = dx > 0 ? 1 : -1;
    int sign_y = dy > 0 ? 1 : -1;
    int n = std::max(dx * sign_x, dy * sign_y);

    float e = -1 / 2.0f, de, ie, iex, iey, ix, iy;
    if (dx * sign_x > dy * sign_y) {
        de = (sign_y * dy) / (sign_x * dx);
        ie = -1;
        iex = 0;
        iey = sign_y;
        ix = sign_x;
        iy = 0;
    } else {
        de = (sign_x * dx) / (sign_y * dy);
        ie = -1;
        iex = sign_x;
        iey = 0;
        ix = 0;
        iy = sign_y;
    }
    for (int wid = 0; wid <= n; wid++) {
        (*ps).push_back(Pixel(x, y));
        x += ix;
        y += iy;
        e += de;
        if (e >= 0) {
            e += ie;
            x += iex;
            y += iey;
        }
    }
}

void bresenham_integer(std::pair<float, float> begin, std::pair<float, float> end,
                       std::vector<Pixel>* ps) {
    int x = begin.first, dx = end.first - begin.first;
    int y = begin.second, dy = end.second - begin.second;
    int sign_x = dx > 0 ? 1 : -1;
    int sign_y = dy > 0 ? 1 : -1;
    int n = std::max(dx * sign_x, dy * sign_y);

    int e, de, ie, iex, iey, ix, iy;
    if (dx * sign_x > dy * sign_y) {
        e = -dx * sign_x;
        de = 2 * dy * sign_y;
        ie = -2 * dx * sign_x;
        iex = 0;
        iey = sign_y;
        ix = sign_x;
        iy = 0;
    } else {
        e = -dy * sign_y;
        de = 2 * dx * sign_x;
        ie = -2 * dy * sign_y;
        iex = sign_x;
        iey = 0;
        ix = 0;
        iy = sign_y;
    }
    for (int wid = 0; wid <= n; wid++) {
        (*ps).push_back(Pixel(x, y));
        x += ix;
        y += iy;
        e += de;
        if (e >= 0) {
            e += ie;
            x += iex;
            y += iey;
        }
    }
}

void mid_point(std::pair<float, float> begin, std::pair<float, float> end, std::vector<Pixel>* ps) {
    int n = std::max(abs(begin.first - end.first), abs(begin.second - end.second));

    int x = begin.first, dx = end.first - begin.first;
    int y = begin.second, dy = end.second - begin.second;
    int sign_x = dx > 0 ? 1 : -1;
    int sign_y = dy > 0 ? 1 : -1;

    int d, increE, incrNE, ix, iy, iex = sign_x, iey = sign_y;
    if (dx * sign_x > dy * sign_y) {
        d = 2 * sign_y * dy - sign_x * dx;
        increE = 2 * dy * sign_y;
        incrNE = 2 * (sign_y * dy - sign_x * dx);
        ix = sign_x;
        iy = 0;
    } else {
        d = 2 * sign_x * dx - sign_y * dy;
        increE = 2 * dx * sign_x;
        incrNE = 2 * (sign_x * dx - sign_y * dy);
        ix = 0;
        iy = sign_y;
    }
    for (int wid = 0; wid <= n; wid++) {
        (*ps).push_back(Pixel(x, y));
        if (d < 0) {
            d += increE;
            x += ix;
            y += iy;
        } else {
            d += incrNE;
            x += iex;
            y += iey;
        }
    }
}

void Gupta_Sproull_algorithm(std::pair<float, float> begin, std::pair<float, float> end,
                             std::vector<Pixel>* ps) {
    auto IntensifyPixel = [=](int x, int y, float brightness) -> void {
        if (abs(brightness) < 1)
            (*ps).push_back(Pixel(x, y, abs(brightness) * 255));
    };
    int n = std::max(abs(begin.first - end.first), abs(begin.second - end.second));

    int x = begin.first, dx = end.first - begin.first;
    int y = begin.second, dy = end.second - begin.second;
    int sign_x = dx > 0 ? 1 : -1;
    int sign_y = dy > 0 ? 1 : -1;

    int d, dvar, increE, incrNE, ix, iy, iex = sign_x, iey = sign_y, x_shift, y_shift;

    int numerator = 0;
    double inv_denominator = 1.0 / (2.0 * sqrt(dx * dx + dy * dy));

    if (dx * sign_x > dy * sign_y) {
        d = 2 * sign_y * dy - sign_x * dx;
        increE = 2 * dy * sign_y;
        incrNE = 2 * (sign_y * dy - sign_x * dx);
        ix = sign_x;
        iy = 0;

        dvar = sign_x * dx;
        x_shift = 0;
        y_shift = sign_y;
    } else {
        d = 2 * sign_x * dx - sign_y * dy;
        increE = 2 * dx * sign_x;
        incrNE = 2 * (sign_x * dx - sign_y * dy);
        ix = 0;
        iy = sign_y;

        dvar = sign_y * dy;
        x_shift = sign_x;
        y_shift = 0;
    }
    for (int wid = 0; wid <= n; wid++) {
        IntensifyPixel(x, y, numerator * inv_denominator);
        IntensifyPixel(x + x_shift, y + y_shift, (2.0 * dvar - numerator) * inv_denominator);
        IntensifyPixel(x - x_shift, y - y_shift, (2.0 * dvar + numerator) * inv_denominator);
        if (d < 0) {
            numerator = d + dvar;
            d += increE;
            x += ix;
            y += iy;
        } else {
            numerator = d - dvar;
            d += incrNE;
            x += iex;
            y += iey;
        }
    }
}

void Xiaolin_Wu_algorithm(std::pair<float, float> begin, std::pair<float, float> end,
                          std::vector<Pixel>* ps) {
    auto plot = [=](int x, int y, float brightness) -> void {
        if (brightness > 0)
            (*ps).push_back(Pixel(x, y, (1 - brightness) * 255));
    };
    auto ipart = [](float x) -> int {
        return int(std::floor(x));
    };
    auto fpart = [](float x) -> float {
        return x - std::floor(x);
    };
    auto rfpart = [=](float x) -> float {
        return 1 - fpart(x);
    };

    float x0 = begin.first, y0 = begin.second, x1 = end.first, y1 = end.second;

    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    const float dx = x1 - x0;
    const float dy = y1 - y0;
    const float gradient = (dx == 0) ? 1 : dy / dx;

    int xpx11;
    float intery;
    {
        const float xend = round(x0);
        const float yend = y0;
        const float xgap = rfpart(x0 + 0.5);
        xpx11 = int(xend);
        const int ypx11 = ipart(yend);
        if (steep) {
            plot(ypx11, xpx11, rfpart(yend) * xgap);
            plot(ypx11 + 1, xpx11, fpart(yend) * xgap);
        } else {
            plot(xpx11, ypx11, rfpart(yend) * xgap);
            plot(xpx11, ypx11 + 1, fpart(yend) * xgap);
        }
        intery = yend + gradient;
    }

    int xpx12;
    {
        const float xend = round(x1);
        const float yend = y1;
        const float xgap = rfpart(x1 + 0.5);
        xpx12 = int(xend);
        const int ypx12 = ipart(yend);
        if (steep) {
            plot(ypx12, xpx12, rfpart(yend) * xgap);
            plot(ypx12 + 1, xpx12, fpart(yend) * xgap);
        } else {
            plot(xpx12, ypx12, rfpart(yend) * xgap);
            plot(xpx12, ypx12 + 1, fpart(yend) * xgap);
        }
    }

    if (steep) {
        for (int x = xpx11 + 1; x < xpx12; x++) {
            plot(ipart(intery), x, rfpart(intery));
            plot(ipart(intery) + 1, x, fpart(intery));
            intery += gradient;
        }
    } else {
        for (int x = xpx11 + 1; x < xpx12; x++) {
            plot(x, ipart(intery), rfpart(intery));
            plot(x, ipart(intery) + 1, fpart(intery));
            intery += gradient;
        }
    }
}
