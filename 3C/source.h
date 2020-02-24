#ifndef SOURCE_H
#define SOURCE_H


#include "image.h"


class Source
{



public:

    virtual void Execute() = 0;
    Image* GetOutput();


protected:
    Image image;

};

#endif
