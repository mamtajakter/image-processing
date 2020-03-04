#include "image.h"
#include "source.h"
#include <stdlib.h>
#include <stdio.h>


 Image::Image(){
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

   Pixel *pixel = (Pixel *)malloc(this->w * this->h * sizeof(Pixel));

     for (int i = 0; i < this -> w; i++) {
       for (int j = 0; j < this -> h; j++) {
         pixel[i* (this -> w) +j] = img.buffer [i* (this -> w) +j];
       }
     }
  this -> buffer = pixel;


}


 Image::~Image(){

}


int Image::getWidth()
{
    return this->w;
}

int Image::getHeight()
{
    return this->h;
}

int Image::getMaxVal()
{
    return this->mv;
}

Pixel* Image::getBuffer()
{
    return this->buffer;
}

void Image::setWidth(int w)
{
   this->w = w;
}

void Image::setHeight(int h)
{
   this->h =h;
}

void Image::setMaxVal(int mv)
{
     this->mv=mv;
}

void Image::setBuffer(Pixel* buf)
{
    this->buffer = buf;
}


void Image::ResetSize(int w, int h)
{

    this->w = w;
    this->h = h;
    this->mv = 255;
    Pixel *pixel = (Pixel *)malloc(w * h * sizeof(Pixel));
    this->buffer = pixel;
}

Source*  Image::getSource(){
    return this-> s ;
};

void  Image::setSource(Source* source){
    s = source;
};


void  Image::Update(void){
  // if (s != NULL){ 
    s ->Update();
  // }
};