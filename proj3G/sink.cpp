#include "sink.h"
#include <stddef.h>

Sink::Sink()
{
    inputA = NULL;
    inputB = NULL;
}

Sink::~Sink(){
    ;
}

Image* Sink::GetInput()
{
    return inputA;
}

void Sink::SetInput(Image *image)
{
    inputA = image;
}

Image* Sink::GetInput2()
{
    return inputB;
}

void Sink::SetInput2(Image *image)
{
    inputB = image;
}