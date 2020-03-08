#include "PNMreader.h"
#include "logging.h"

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

const char *PNMreader :: SourceName()
{
    return "PNMreader";
}

void PNMreader::Execute()
{

    char magicNum[128];
    int width, height, maxval;
    FILE *f_in= fopen ( filename.c_str(), "rb");
    if (f_in == NULL)
    {
        fprintf(stderr, "Unable to open the file!\nExiting\n");
        exit(EXIT_FAILURE);
    }

    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr,"File is not in pnm P6 format\nExiting\n");
        exit(EXIT_FAILURE);
    }

//
    // if (f_in == NULL){
    //   fprintf(stderr, "Cannot find the file path %s\n",(this -> filename).c_str() );
    //   return;
    // }
    //
    // if(strcmp(magicNum, "P6")!=0){
    //   fprintf(stderr, " %s File is not in P6 format\n",(this -> filename).c_str() );
    //   return;
    // }

    unsigned char rr, gg, bb;
    int index;
    Pixel *inputBuffer = output.getBuffer();

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {

            fscanf(f_in, "%c%c%c", &rr, &gg, &bb);

            index=i * width + j;

            inputBuffer[index].r = rr;
            inputBuffer[index].g = gg;
            inputBuffer[index].b = bb;
        }

    fclose(f_in);

}

void PNMreader::Update(){
    char msg[128];
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);

};

