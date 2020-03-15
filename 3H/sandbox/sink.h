#ifndef SINK_H
#define SINK_H


#include "image.h"


class Sink
{


public:
    Sink();
    virtual ~Sink();
    void SetInput(Image *img);
    void SetInput2(Image *img);
    Image* GetInput();
    Image* GetInput2();


protected:
    Image *inputA, *inputB;

};

#endif
