#ifndef IMAGE_H
#define IMAGE_H


typedef struct
{
    unsigned char r,g,b;
} Pixel;

class Source;

class Image
{
private:
    Pixel* buffer;
    int w, h, mv;
    Source *s;
public:
    Image();
    Image(Pixel *buf, int w, int h, int mv);
    Image (Image &);

    virtual ~Image();

    int getWidth();
    int getHeight();
    int getMaxVal();
    Pixel* getBuffer();

    void setWidth(int w);
    void setHeight(int h);
    void setMaxVal(int mv);
    void setBuffer(Pixel* buf);

    void ResetSize(int w, int h);

    Source* getSource();
    void    setSource(Source*);
    
    void    Update();
};

#endif
