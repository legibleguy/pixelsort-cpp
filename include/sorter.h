#pragma once
#include "image.h"
#include <vector>
#include <functional>

enum class SortMode {
    Brightness,
    Hue,
    Saturation
};

enum class Direction {
    Horizontal,
    Vertical
};

class PixelSorter {
public:
    PixelSorter(SortMode mode, Direction direction, float threshold = 0.0f);
    
    void sort(Image& image);

private:
    void sortRow(std::vector<Pixel>& pixels);
    void sortColumn(std::vector<Pixel>& pixels);
    bool shouldSort(const Pixel& pixel) const;
    
    SortMode m_mode;
    Direction m_direction;
    float m_threshold;
    std::function<float(const Pixel&)> m_sortKey;
};
