#ifndef FILTER_H
#define FILTER_H
#include "sink.h"
#include "source.h"




class Filter : public Source, public Sink
{
public:
    Filter();
    virtual ~Filter();
    // virtual void Execute() = 0;
    virtual void Update() ;

    virtual const char *SourceName();
    virtual const char *SinkName();

    virtual const char *FilterName() = 0;
};


class Shrinker : public Filter
{
public:
    // Shrinker();
    // virtual ~Shrinker();
    virtual void Execute() ;
    // virtual void Update() ;
    virtual const char *FilterName();

};


class LRCombine :public Filter
{

public:
    // LRCombine();
    // virtual ~LRCombine();
    virtual void Execute() ;
    // virtual void Update() ;
    virtual const char *FilterName();

};


class TBCombine: public Filter
{

public:
    // TBCombine();
    // virtual ~TBCombine();
    virtual void Execute() ;
    // virtual void Update() ;
    virtual const char *FilterName();
};


class Blender : public Filter
{

public:

    // Blender();
    // virtual ~Blender();

    void SetFactor(double f);
    double GetFactor();

    virtual void Execute() ;
    // virtual void Update() ;
    virtual const char *FilterName();


protected:

    double factor;
};

#endif
