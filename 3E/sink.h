#ifndef SINK_H
#define SINK_H


#include "image.h"


class Sink
{


public:

    void SetInput(Image *img);
    void SetInput2(Image *img);


protected:
    Image *imageA, *imageB;

};

#endif
