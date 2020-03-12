#include "source.h"
#include "logging.h"

Source::Source(){
    output.setSource(this);
}

Source::~Source(){
    ;
}

Image* Source::GetOutput()
{
    return &output;
}


void Source::SetOutput(Image img){

    output = img;
}

