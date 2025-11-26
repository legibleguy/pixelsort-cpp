#include "sorter.h"
#include <algorithm>

PixelSorter::PixelSorter(SortMode mode, Direction direction, float threshold)
    : m_mode(mode), m_direction(direction), m_threshold(threshold) {
    
    switch (mode) {
        case SortMode::Brightness:
            m_sortKey = [](const Pixel& p) { return p.brightness(); };
            break;
        case SortMode::Hue:
            m_sortKey = [](const Pixel& p) { return p.hue(); };
            break;
        case SortMode::Saturation:
            m_sortKey = [](const Pixel& p) { return p.saturation(); };
            break;
    }
}

void PixelSorter::sort(Image& image) {
    if (m_direction == Direction::Horizontal) {
        for (int y = 0; y < image.height(); ++y) {
            auto row = image.getRow(y);
            sortRow(row);
            image.setRow(y, row);
        }
    } else {
        for (int x = 0; x < image.width(); ++x) {
            auto column = image.getColumn(x);
            sortColumn(column);
            image.setColumn(x, column);
        }
    }
}

void PixelSorter::sortRow(std::vector<Pixel>& pixels) {
    std::stable_sort(pixels.begin(), pixels.end(), 
        [this](const Pixel& a, const Pixel& b) {
            if (shouldSort(a) && shouldSort(b)) {
                return m_sortKey(a) < m_sortKey(b);
            }
            return false;
        });
}

void PixelSorter::sortColumn(std::vector<Pixel>& pixels) {
    sortRow(pixels); // Same logic
}

bool PixelSorter::shouldSort(const Pixel& pixel) const {
    return pixel.brightness() >= m_threshold;
}