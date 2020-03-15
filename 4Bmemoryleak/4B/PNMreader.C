#include "PNMreader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PNMreader::PNMreader(string filen)
{
    filename= filen;
}

PNMreader::~PNMreader()
{
      filename.clear();
}


void PNMreader::Execute()
{

    char magicNum[128];
    int width, height, maxval;
    FILE *f_in= fopen ( filename.c_str(), "rb");
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);



    unsigned char rr, gg, bb;
    int index;

    output.ResetSize(width, height);
    
    Pixel *outputBuffer = output.getBuffer();


 	  for (int i = 0; i < height; i++)
 		  for (int j = 0; j < width; j++) {

 			   fscanf(f_in, "%c%c%c", &rr, &gg, &bb);

               index=i * width + j;

 		 	   outputBuffer[index].r = rr;
 		  	   outputBuffer[index].g = gg;
 			   outputBuffer[index].b = bb;
 		 }

 	 fclose(f_in);

}

void PNMreader::Update(){
    Execute();  

};

