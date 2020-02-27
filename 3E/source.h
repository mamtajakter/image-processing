#ifndef SOURCE_H
#define SOURCE_H


#include "image.h"


class Source
{



public:


    Image* GetOutput();
    virtual void Update() = 0;


protected:
    Image image;
    virtual void Execute() = 0;

};

#endif
