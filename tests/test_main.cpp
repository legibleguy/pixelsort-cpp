#include "../include/image.h"
#include "../include/sorter.h"
#include <iostream>
#include <cassert>

void testPixelBrightness() {
    Pixel white{255, 255, 255, 255};
    Pixel black{0, 0, 0, 255};
    
    assert(white.brightness() > 0.99f);
    assert(black.brightness() < 0.01f);
    
    std::cout << "✓ Pixel brightness test passed\n";
}

void testImageCreation() {
    Image img;
    assert(img.width() == 0);
    assert(img.height() == 0);
    
    std::cout << "✓ Image creation test passed\n";
}

int main() {
    std::cout << "Running tests...\n";
    
    testPixelBrightness();
    testImageCreation();
    
    std::cout << "All tests passed!\n";
    return 0;
}