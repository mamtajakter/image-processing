#include "PNMwriter.h"

#include <stdio.h>
#include <stdlib.h>

void PNMwriter::Write(char *filename)
{
  FILE *f_out = fopen (filename, "wb");

  fprintf (f_out, "P6\n");// first line "P6"
  fprintf (f_out, "%d %d\n", imageA->getWidth(), imageA->getHeight());// second line "1786 1344"
  fprintf (f_out, "%d\n", imageA->getMaxVal());// third line "255"

  int index;
  Pixel *outputputBuffer = imageA->getBuffer();

  for (int i = 0; i < imageA->getHeight(); i++)
    for (int j = 0; j < imageA->getWidth(); j++){

      index=i * imageA->getWidth() + j;
      fprintf(f_out, "%c%c%c", outputputBuffer[index].r, outputputBuffer[index].g, outputputBuffer[index].b);
      
    }



fclose(f_out);

}
