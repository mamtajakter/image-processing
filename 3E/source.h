#ifndef SOURCE_H
#define SOURCE_H


#include "image.h"


class Source
{



public:
	Source();
	virtual ~Source();
    Image* GetOutput();
	virtual void Update() ;


protected:
    Image output;
    virtual void Execute() = 0;
    

};

#endif
