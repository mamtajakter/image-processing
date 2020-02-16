#include <pixel.h>
#ifndef IMAGE_H
#define IMAGE_H

// A pixel


// A pointer to array of pixels
struct Image
{



    /* data members go here */
    Pixel *buffer;// array of pointers -- a buffer to store image data
    int w, h;
    int mv;

    Image(void);
    Image(Pixel *buf, int w, int h, int mv);
    Image (Image &);
    void ResetSize(int w, int h);
} ;
#endif
