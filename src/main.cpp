#include "image.h"
#include "sorter.h"
#include <iostream>
#include <string>

void printUsage(const char* program) {
    std::cout << "Usage: " << program << " <input> <output> [options]\n"
              << "Options:\n"
              << "  --mode <brightness|hue|saturation>  Sort mode (default: brightness)\n"
              << "  --direction <horizontal|vertical>   Sort direction (default: horizontal)\n"
              << "  --threshold <0.0-1.0>              Brightness threshold (default: 0.0)\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string input = argv[1];
    std::string output = argv[2];
    
    SortMode mode = SortMode::Brightness;
    Direction direction = Direction::Horizontal;
    float threshold = 0.0f;
    
    // Parse arguments
    for (int i = 3; i < argc; i += 2) {
        if (i + 1 >= argc) break;
        
        std::string arg = argv[i];
        std::string value = argv[i + 1];
        
        if (arg == "--mode") {
            if (value == "brightness") mode = SortMode::Brightness;
            else if (value == "hue") mode = SortMode::Hue;
            else if (value == "saturation") mode = SortMode::Saturation;
        } else if (arg == "--direction") {
            if (value == "horizontal") direction = Direction::Horizontal;
            else if (value == "vertical") direction = Direction::Vertical;
        } else if (arg == "--threshold") {
            threshold = std::stof(value);
        }
    }
    
    Image image;
    if (!image.load(input)) {
        std::cerr << "Failed to load image: " << input << "\n";
        return 1;
    }
    
    std::cout << "Loaded image: " << image.width() << "x" << image.height() << "\n";
    
    PixelSorter sorter(mode, direction, threshold);
    sorter.sort(image);
    
    if (!image.save(output)) {
        std::cerr << "Failed to save image: " << output << "\n";
        return 1;
    }
    
    std::cout << "Saved to: " << output << "\n";
    return 0;
}