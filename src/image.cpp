#include "image.h"
#include <cmath>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

float Pixel::brightness() const {
    return (0.299f * r + 0.587f * g + 0.114f * b) / 255.0f;
}

float Pixel::hue() const {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;
    
    float max_val = std::max({rf, gf, bf});
    float min_val = std::min({rf, gf, bf});
    float delta = max_val - min_val;
    
    if (delta < 0.00001f) return 0.0f;
    
    float hue = 0.0f;
    if (max_val == rf) {
        hue = 60.0f * fmod((gf - bf) / delta, 6.0f);
    } else if (max_val == gf) {
        hue = 60.0f * ((bf - rf) / delta + 2.0f);
    } else {
        hue = 60.0f * ((rf - gf) / delta + 4.0f);
    }
    
    return hue < 0 ? hue + 360.0f : hue;
}

float Pixel::saturation() const {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;
    
    float max_val = std::max({rf, gf, bf});
    float min_val = std::min({rf, gf, bf});
    
    if (max_val < 0.00001f) return 0.0f;
    
    return (max_val - min_val) / max_val;
}

Image::Image() : m_width(0), m_height(0), m_channels(0), m_data(nullptr) {}

Image::~Image() {
    if (m_data) {
        stbi_image_free(m_data);
    }
}

bool Image::load(const std::string& filename) {
    m_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, 4);
    m_channels = 4; // Force RGBA
    return m_data != nullptr;
}

bool Image::save(const std::string& filename) {
    return stbi_write_png(filename.c_str(), m_width, m_height, m_channels, m_data, m_width * m_channels) != 0;
}

Pixel Image::getPixel(int x, int y) const {
    int index = (y * m_width + x) * m_channels;
    Pixel p;
    p.r = m_data[index];
    p.g = m_data[index + 1];
    p.b = m_data[index + 2];
    p.a = m_data[index + 3];
    return p;
}

void Image::setPixel(int x, int y, const Pixel& pixel) {
    int index = (y * m_width + x) * m_channels;
    m_data[index] = pixel.r;
    m_data[index + 1] = pixel.g;
    m_data[index + 2] = pixel.b;
    m_data[index + 3] = pixel.a;
}

std::vector<Pixel> Image::getRow(int y) const {
    std::vector<Pixel> row;
    row.reserve(m_width);
    for (int x = 0; x < m_width; ++x) {
        row.push_back(getPixel(x, y));
    }
    return row;
}

std::vector<Pixel> Image::getColumn(int x) const {
    std::vector<Pixel> column;
    column.reserve(m_height);
    for (int y = 0; y < m_height; ++y) {
        column.push_back(getPixel(x, y));
    }
    return column;
}

void Image::setRow(int y, const std::vector<Pixel>& pixels) {
    for (int x = 0; x < m_width && x < static_cast<int>(pixels.size()); ++x) {
        setPixel(x, y, pixels[x]);
    }
}

void Image::setColumn(int x, const std::vector<Pixel>& pixels) {
    for (int y = 0; y < m_height && y < static_cast<int>(pixels.size()); ++y) {
        setPixel(x, y, pixels[y]);
    }
}