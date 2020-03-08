#ifndef SOURCE_H
#define SOURCE_H


#include "image.h"


class Source
{



public:
    Source();
    virtual ~Source();

    Image* GetOutput();
    void SetOutput(Image img);

    virtual void Update() ;


protected:
    Image output;
    virtual void Execute() = 0;
    virtual const char *SourceName() = 0;


};

#endif