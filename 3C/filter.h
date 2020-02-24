#ifndef FILTER_H
#define FILTER_H
#include "sink.h"
#include "source.h"


class Filter : public Source, public Sink
{
public:
  ;
};


class Shrinker : public Filter
{
public:
    void Execute();

};


class LRCombine :public Filter
{

public:
    void Execute();

};


class TBCombine: public Filter
{

public:

    void Execute();
};


class Blender : public Filter
{

public:
    void SetFactor(double f);
    double GetFactor();
    void Execute();


protected:

    double factor;
};

#endif
