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


class Mirror : public Filter
{
public:
    virtual void Execute();
    virtual const char *FilterName();

};

class Rotate : public Filter
{
public:
    virtual void Execute();
    virtual const char *FilterName();

};

class Subtract : public Filter
{
public:
    virtual void Execute();
    virtual const char *FilterName();

};

class Grayscale : public Filter
{
public:
    //Grayscale(void);
    virtual void Execute();
    virtual const char *FilterName();

};

class Blur : public Filter
{
public:
    virtual void Execute();
    virtual const char *FilterName();

};

class Color : public Source
{
private:
    int width, height;
    unsigned char red, green, blue;
public:
    Color(void);
    Color(int width, int height, unsigned char r, unsigned char g, unsigned char b);
    virtual void Execute();
    virtual void Update();
    virtual const char *SourceName(){return "Color";}

};

class CheckSum : public Sink
{
public:
    virtual void OutputCheckSum(const char *filename);
    virtual const char *SinkName(){return "CheckSum";}

};
#endif
