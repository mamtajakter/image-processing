#ifndef FILTER_H
#define FILTER_H
#include "sink.h"
#include "source.h"


class Filter : public Source, public Sink
{
public:
     Filter();
     virtual ~Filter();

     virtual void 	Execute() = 0;
     virtual void 	Update() = 0;
  ;
};


class Shrinker : public Filter
{
public:
    Shrinker();
    virtual ~Shrinker();

    virtual void Execute();
    virtual void Update();



};


class LRCombine :public Filter
{

public:
  LRCombine();
  virtual ~LRCombine();

  virtual void Execute();
  virtual void Update();



};


class TBCombine: public Filter
{

public:
  TBCombine();
  virtual ~TBCombine();

  virtual void Execute();
  virtual void Update();

};


class Blender : public Filter
{

public:
    Blender();
    virtual ~TBCombine();

    virtual void Execute();
    virtual void Update();

    void SetFactor(double f);
    double GetFactor();



protected:

    double factor;
};

#endif
