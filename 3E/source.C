#include "source.h"

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

void Source :: Update()
{
    Execute();
}
