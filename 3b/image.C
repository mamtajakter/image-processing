#include <pixel.h>
#include <image.h>
#include <stdlib.h>
#include <stdio.h>

Image::Image(void){
   this->w=1786;
   this->h=1344;
   this->mv=255;

   this->buffer = (Pixel *) malloc(sizeof(Pixel)*this->w*this->h);


}

Image::Image(Pixel *buf, int w, int h, int mv){
   this->w=w;
   this->h=h;
   this->mv=mv;

   this->buffer = buf;


}

Image::Image(Image &img){
   this->w=img.w;
   this->h=img.h;
   this->mv=img.mv;

   this->buffer = (Pixel *) malloc(sizeof(Pixel)*this->w*this->h);


}


void Image::ResetSize(int w, int h){
  this->w=w;
  this->h=h;
}
