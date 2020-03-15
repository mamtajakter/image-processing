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
    void Update() ;
    static int numOfCalls;

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
    virtual const char *FilterName();
    virtual void Execute();

};

class Rotate : public Filter
{

public:

    virtual const char *FilterName();
    virtual void Execute();

};

class Subtract : public Filter
{

public:

    virtual const char *FilterName();
    virtual void Execute();


};


class Grayscale : public Filter
{

public:

    virtual const char *FilterName();
    virtual void Execute();

};

class Blur : public Filter
{

public:
    
    virtual const char *FilterName();
    virtual void Execute();

};

class Color : public Filter
{

public:

    Color(void);
    Color(int width, int height, unsigned char r, unsigned char g, unsigned char b);

    virtual void Execute();

    virtual const char *FilterName();

private:
    
    unsigned char red, green, blue;
    int width, height;


};

class CheckSum : public Sink
{

public:
    
    virtual const char *SinkName(); 
    virtual void OutputCheckSum(const char *filename);

};

#endif
