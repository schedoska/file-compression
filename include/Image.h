#ifndef __Image_H__
#define __Image_H__

#include <iostream>
#include <list>
#include <unordered_map>

class Image {
public:
    Image(unsigned width, unsigned height);
    Image(double**, unsigned, unsigned);
    Image();
    ~Image();
    Image(const Image&);
    Image& operator=(const Image&);

    inline double& operator()(unsigned x, unsigned y) { return p[y][x]; }
    void printImageData();

    unsigned GetHeight() { return height; }
    unsigned GetWidth() { return width; }
    int Compare(Image image);
    std::unordered_map<int, int> HistogramData();
    float EntropyValue();
    double Value(int x, int y);

private:
    unsigned height, width;
    double** p;

    void allocSpace();
};

namespace ImageIO {
    Image ReadImage(std::string fileName);
    void WriteImage(Image image, std::string fileName);
    void WriteHistogramData(std::unordered_map<int, int> histogram, std::string fileName);
}

#endif
