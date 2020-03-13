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

//void Source :: Update()
//{
//    char	msg[128];
//    sprintf(msg,	"%s:	about	to	execute",	SourceName());
//    Logger::LogEvent(msg);
//    Execute();
//    sprintf(msg,	"%s:	done	executing",	SourceName());
//    Logger::LogEvent(msg);
//}
