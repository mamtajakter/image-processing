#include "image.h"
#include "source.h"
#include <stdlib.h>
#include <stdio.h>


 Image::Image(){
   ResetSize(w,h);

}



Image::Image(Pixel *buf, int ww, int hh, int mvv){
   w=ww;
   h=hh;
   mv=mvv;

   buffer = buf;


}

Image::Image(Image &img){

   w=img.w;
   h=img.h;
   mv=img.mv;

   Pixel *pixel = (Pixel *)malloc(w * h * sizeof(Pixel));

     for (int i = 0; i <  w; i++) {
       for (int j = 0; j <  h; j++) {
         pixel[i*  w +j] = img.buffer [i*  w +j];
       }
     }
  buffer = pixel;


}


 Image::~Image(){

}

  void Image::BufferClean()
{
    if (!buffer) 
        return;
    delete[] buffer;
    buffer = 0;
}

int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

int Image::getMaxVal()
{
    return mv;
}

Pixel* Image::getBuffer()
{
    return buffer;
}

void Image::setWidth(int ww)
{
   w = ww;
}

void Image::setHeight(int hh)
{
   h =hh;
}

void Image::setMaxVal(int mvv)
{
     mv=mvv;
}

void Image::setBuffer(Pixel* buf)
{
    buffer = buf;
}


void Image::ResetSize(int ww, int hh)
{

   //cleanup existing buffer if there is any
    // BufferClean();
    w = ww;
    h = hh;
    mv = 255;
    Pixel *pixel = (Pixel *)malloc(w * h * sizeof(Pixel));
    buffer = pixel;
}

Source*  Image::getSource(){
    return  s ;
};

void  Image::setSource(Source* source){
    BufferClean();
    s = source;
};

void Image::SourceClean()
{
    if (s)
       s->SourceClean();
}

void  Image::Update(void){
  if (s != NULL)
       s ->Update();
  
};