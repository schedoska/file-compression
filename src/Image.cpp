#include "../include/Image.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <bitset>
#include <cstdint>
#include <sstream>

Image::Image(unsigned width_, unsigned height_)
    : height(height_), width(width_)
{
    allocSpace();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            p[i][j] = 0;
        }
    }
}

Image::Image(double** a, unsigned rows, unsigned cols) : height(rows), width(cols)
{
    allocSpace();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            p[i][j] = a[i][j];
        }
    }
}

Image::Image() : height(1), width(1)
{
    allocSpace();
    p[0][0] = 0;
}

Image::~Image()
{
    for (int i = 0; i < height; ++i) {
        delete[] p[i];
    }
    delete[] p;
}

Image::Image(const Image& m) : height(m.height), width(m.width)
{
    allocSpace();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
}

Image& Image::operator=(const Image& m)
{
    if (this == &m) {
        return *this;
    }

    if (height != m.height || width != m.width) {
        for (int i = 0; i < height; ++i) {
            delete[] p[i];
        }
        delete[] p;

        height = m.height;
        width = m.width;
        allocSpace();
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
    return *this;
}

void Image::printImageData()
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << p[y][x] << " ";
        }
        std::cout << "\n";
    }
}

int Image::Compare(Image image)
{
    int e = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            e += std::abs(image.p[y][x] - p[y][x]);
        }
    }
    return e;
}

void Image::allocSpace()
{
    p = new double* [height];
    for (int i = 0; i < height; ++i) {
        p[i] = new double[width];
    }
}

namespace ImageIO {
    Image ReadImage(std::string fileName) {
        std::string inputLine;
        std::fstream file(fileName, std::fstream::in | std::fstream::binary);

        std::getline(file, inputLine);
        if (inputLine.substr(0, 2) != "P5") return Image(1, 1);
        
        do { std::getline(file, inputLine); } while (inputLine[0] == '#');
        std::stringstream ss(inputLine);

        int w, h;
        ss >> w >> h;
        int scale;
        file >> scale;
        char a;
        file.read(&a, 1);

        Image image(w, h);

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                file.read(&a, 1);
                image(x,y) = (uint8_t)a;
            }
        }
        file.close();
        return image;
    }

    void WriteImage(Image image, std::string fileName) {
        int w = image.GetWidth();
        int h = image.GetHeight();

        std::fstream file(fileName, std::fstream::out | std::fstream::binary);
        file << "P5\n" << w << " " << h << "\n255\n";

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                char val = image(x, y);
                file.write(&val, sizeof(val));
            }
        }
    }
}
