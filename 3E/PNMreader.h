#ifndef PNM_READER_H
#define PNM_READER_H


#include "source.h"
#include <string>

using namespace std;
class PNMreader : public Source
{


public:
    PNMreader(string filename);
    void Execute();

    virtual ~PNMreader();


private:

    string filename;

};

#endif
