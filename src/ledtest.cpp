#include <cstdio>
#include <cstdlib>
//#include <cstdint>
#include <cstring>
#include <ctime>
//#include <cinttypes>
#include <cerrno>
//#include <unistd.h>
#include <pixel.hpp>


int main(void) {
    
    uint8_t rgb[3];
    const int num_pixels = 8;
    PixelBone_Pixel *const strip = new PixelBone_Pixel(num_pixels);
    
    
    while (1) {
        //for (unsigned p = 0; p < num_pixels; p++) 
        //{
            //strip->setPixelColor(p, 0, (25 * p), (255 - (25 * p)));
            strip->setPixelColor(0, 0, 0, 255);
            strip->setPixelColor(1, 0, 150, 75);
            strip->setPixelColor(2, 0, 200, 50);
            strip->setPixelColor(3, 0, 250, 0);
            strip->setPixelColor(4, 50, 250, 0);
            strip->setPixelColor(5, 125, 175, 0);
            strip->setPixelColor(6, 175, 175, 0);
            strip->setPixelColor(7, 255, 150, 0);
        //}
        strip->wait();
        strip->show();

    }

    delete strip;
}
