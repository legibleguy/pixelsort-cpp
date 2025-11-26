#pragma once
#include <string>
#include <vector>
#include <memory>

struct Pixel {
    unsigned char r, g, b, a;
    
    float brightness() const;
    float hue() const;
    float saturation() const;
};

class Image {
public:
    Image();
    ~Image();
    
    bool load(const std::string& filename);
    bool save(const std::string& filename);
    
    int width() const { return m_width; }
    int height() const { return m_height; }
    int channels() const { return m_channels; }
    
    Pixel getPixel(int x, int y) const;
    void setPixel(int x, int y, const Pixel& pixel);
    
    std::vector<Pixel> getRow(int y) const;
    std::vector<Pixel> getColumn(int x) const;
    
    void setRow(int y, const std::vector<Pixel>& pixels);
    void setColumn(int x, const std::vector<Pixel>& pixels);

private:
    int m_width;
    int m_height;
    int m_channels;
    unsigned char* m_data;
};
