//
// Created by Mamtaj Akter on 2020-03-07.
//

#include "PNMwriter.h"

#include <stdio.h>
#include <stdlib.h>

void PNMwriter::Write(char *filename)
{
    FILE *f_out = fopen (filename, "wb");

    fprintf (f_out, "P6\n");// first line "P6"
    fprintf (f_out, "%d %d\n", inputA->getWidth(), inputA->getHeight());// second line "1786 1344"
    fprintf (f_out, "%d\n", inputA->getMaxVal());// third line "255"

    int index;
    Pixel *outputputBuffer = inputA->getBuffer();

    for (int i = 0; i < inputA->getHeight(); i++)
        for (int j = 0; j < inputA->getWidth(); j++){

            index=i * inputA->getWidth() + j;
            fprintf(f_out, "%c%c%c", outputputBuffer[index].r, outputputBuffer[index].g, outputputBuffer[index].b);

        }


    fclose(f_out);

}
