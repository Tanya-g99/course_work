#pragma once
#include "Pixel.hpp"

#include <vector>
#include <iostream>

void naive_algorithm(std::pair<float,float> begin, std::pair<float,float> end, std::vector<Pixel>* ps);
void digital_differential_analyzer(std::pair<float,float> begin, std::pair<float,float> end, std::vector<Pixel>* ps);
void bresenham_float(std::pair<float,float> begin, std::pair<float,float> end, std::vector<Pixel>* ps);
void bresenham_integer(std::pair<float,float> begin, std::pair<float,float> end, std::vector<Pixel>* ps);
void mid_point(std::pair<float,float> begin, std::pair<float,float> end, std::vector<Pixel>* ps);
void Gupta_Sproull_algorithm(std::pair<float,float> begin, std::pair<float,float> end, std::vector<Pixel>* ps);
void Xiaolin_Wu_algorithm(std::pair<float,float> begin, std::pair<float,float> end, std::vector<Pixel>* ps);
