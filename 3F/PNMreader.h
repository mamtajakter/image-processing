#ifndef PNM_READER_H
#define PNM_READER_H

#include "PNMreader.h"
#include "source.h"
#include <string>

using namespace std;
class PNMreader : public Source
{


public:
    PNMreader(string filename);
    virtual void	Update();
    virtual void	Execute(void);

    virtual ~PNMreader();
    virtual const char *SourceName();


private:

    string filename;

};

#endif
