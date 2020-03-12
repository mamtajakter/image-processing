//
// Created by Mamtaj Akter on 2020-03-07.
//

#include<stdio.h>
#include<stdlib.h>

#include "filter.h"
#include "logging.h"

Filter::Filter()
{
    // output.setSource(this);
}

Filter::~Filter()
{
    ;
}

int Filter::numOfCalls = 0;
const char *Filter::SourceName()
{
    return FilterName();
}

const char *Filter::SinkName()
{
    return FilterName();
}


void Filter::Update()
{

	numOfCalls++;
	if (numOfCalls > 1000){
		 char msg[1024];
		 sprintf(msg, "Fell in an infinite loop");
		 DataFlowException e(SinkName(), msg);
		 throw e;
	}
    if (inputA != NULL){
        char msg[128];
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        inputA->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
    }


    if (inputB != NULL){
        char msg[128];
        sprintf(msg, "%s: about to update input2", SourceName());
        Logger::LogEvent(msg);
        inputB->Update();
        sprintf(msg, "%s: done updating input2", SourceName());
        Logger::LogEvent(msg);
    }

    char msg[128];
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);

}



const char *Shrinker::FilterName()
{
    return "Shrinker";
}

void Shrinker::Execute()
{
    if(inputA == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    else {
        int outputH = inputA->getHeight() / 2;
        int outputW = inputA->getWidth() / 2;
        int inputIndex, outputIndex;

        output.ResetSize(outputW, outputH);

        Pixel *inputBuffer = inputA->getBuffer();
        Pixel *outputBuffer = output.getBuffer();

        for (int i = 0; i < outputH; i++)
            for (int j = 0; j < outputW; j++) {

                inputIndex = i * 2 * (inputA->getWidth()) + j * 2;
                outputIndex = i * outputW + j;

                outputBuffer[outputIndex] = inputBuffer[inputIndex];
            }
    }
}


const char *LRCombine::FilterName()
{
    return "LRCombine";
}

void LRCombine::Execute()
{
    if(inputA == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(inputB == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(inputA->getHeight() != inputB->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d", SinkName(), inputA->getHeight(),inputB->getHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }


    int i, j;

    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth()+ inputB->getWidth();
    int inputIndex, outputIndex;

    output.ResetSize(outputW, outputH);

    Pixel *inputABuffer = inputA->getBuffer();
    Pixel *inputBBuffer = inputB->getBuffer();
    Pixel *outputBuffer = output.getBuffer();

    for ( i = 0; i < outputH; i++){
        for ( j = 0; j < inputA->getWidth(); j++){

            inputIndex = i * inputA->getWidth() + j;
            outputIndex = i * outputW + j;

            outputBuffer[outputIndex] = inputABuffer[inputIndex];
        }

    }

    for ( i = 0; i < outputH; i++){
        for ( j = inputA->getWidth(); j < outputW; j++){

            inputIndex = i * inputB->getWidth()+ (j-inputA->getWidth());
            outputIndex = i * outputW + j;

            outputBuffer[outputIndex] = inputBBuffer[inputIndex];
        }
    }


}



const char *TBCombine::FilterName()
{
    return "TBCombine";
}

void TBCombine::Execute()
{
    if(inputA == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(inputB == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(inputA->getWidth() != inputB->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), inputA->getWidth(),inputB->getWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i, j;
    int outputH= inputA->getHeight()+inputB->getHeight();
    int outputW= inputA->getWidth();
    int inputIndex, outputIndex;

    output.ResetSize(outputW, outputH);

    Pixel *inputABuffer = inputA->getBuffer();
    Pixel *inputBBuffer = inputB->getBuffer();
    Pixel *outputBuffer = output.getBuffer();


    for ( i = 0; i < inputA->getHeight(); i++){
        for ( j = 0; j < outputW; j++){

            inputIndex = i * inputA->getWidth()+ j;
            outputIndex = i * outputW + j;

            outputBuffer[outputIndex] = inputABuffer[inputIndex];

        }
    }


    for ( i = inputA->getHeight(); i < outputH; i++){
        for ( j = 0; j < outputW; j++){

            inputIndex = (i-inputA->getHeight()) * inputA->getWidth() + j;
            outputIndex = i * outputW + j;

            outputBuffer[outputIndex] = inputBBuffer[inputIndex];
        }
    }


}



void Blender::SetFactor(double f)
{
    factor = f;
}


double Blender::GetFactor(){
    return factor;
}

const char *Blender::FilterName()
{
    return "Blender";
}

void Blender::Execute()
{
    if(inputA == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(inputB == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(inputA->getHeight() != inputB->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d", SinkName(), inputA->getHeight(),inputB->getHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(inputA->getWidth() != inputB->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), inputA->getWidth(),inputB->getWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(factor < 0.0 or factor > 1.0)
    {
        char msg[1024];
        sprintf(msg, "Invalid factor for Blender: %f", factor);
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int index;
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();

    output.ResetSize(outputW, outputH);

    Pixel *inputABuffer = inputA->getBuffer();
    Pixel *inputBBuffer = inputB->getBuffer();
    Pixel *outputBuffer = output.getBuffer();

    for (int i = 0; i < outputH; i++){
        for (int j = 0; j < outputW; j++) {

            index = i*outputW + j;

            Pixel pixelA = inputABuffer[index];
            Pixel pixelB = inputBBuffer[index];

            outputBuffer[index].r = factor*(pixelA).r + (1 - factor)*(pixelB).r;
            outputBuffer[index].g = factor*(pixelA).g + (1 - factor)*(pixelB).g;
            outputBuffer[index].b = factor*(pixelA).b + (1 - factor)*(pixelB).b;
        }
    }

}


const char *Mirror::FilterName()
{
    return "Mirror";
}


void Mirror :: Execute()
{
    if(inputA == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i, j;

    int index;
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();
    int inputIndex, outputIndex;
    Pixel *inputBuffer = inputA->getBuffer();
    Pixel *outputBuffer = output.getBuffer();
    output.ResetSize(outputW, outputH);


    for(i = 0; i < outputH; i++)
    {
        for(j = 0; j < outputW; j++)
        {
            inputIndex = i * outputW + (outputW - 1 - j);
            outputIndex = i * outputW + j;

            outputBuffer[outputIndex] = inputBuffer[inputIndex];
        }
    }
}


const char *Rotate::FilterName()
{
    return "Rotate";
}

void Rotate :: Execute()
{
    if(inputA == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i, j;
    int index;
    int outputW= inputA->getHeight();
    int outputH= inputA->getWidth();
    int inputIndex, outputIndex;
    Pixel *inputBuffer = inputA->getBuffer();
    Pixel *outputBuffer = output.getBuffer();
    output.ResetSize(outputW, outputH);


    for(i = 0; i < outputH; i++)
        for(j= 0; j < outputW; j++)
        {
            inputIndex = (outputW - 1 - j) * outputH + i;
            outputIndex = i * outputW + j;

            outputBuffer[outputIndex] = inputBuffer[inputIndex];
        }
    

}


const char *Subtract::FilterName()
{
    return "Subtract";
}

void Subtract :: Execute()
{

   

    if(inputA == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(inputB == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(inputA->getHeight() != inputB->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d", SinkName(), inputA->getHeight(),inputB->getHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(inputA->getWidth() != inputB->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), inputA->getWidth(),inputB->getWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int i;

     int index;
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();
    int inputIndex, outputIndex;
    Pixel *inputABuffer = inputA->getBuffer();
    Pixel *inputBBuffer = inputB->getBuffer();
    Pixel *outputBuffer = output.getBuffer();
    output.ResetSize(outputW, outputH);

    for(i = 0; i < outputH * outputW; i++)
    {
        if (inputABuffer[i].r < inputBBuffer[i].r) 
            outputBuffer[i].r = 0;
        else 
            outputBuffer[i].r =inputABuffer[i].r - inputBBuffer[i].r;

        if (inputABuffer[i].g < inputBBuffer[i].g) 
            outputBuffer[i].g = 0;
        else 
            outputBuffer[i].g =inputABuffer[i].g - inputBBuffer[i].g;

        if (inputABuffer[i].b < inputBBuffer[i].b) 
            outputBuffer[i].b = 0;
        else 
            outputBuffer[i].b =inputABuffer[i].b - inputBBuffer[i].b;

    }
}


const char *Grayscale::FilterName()
{
    return "Grayscale";
}

void Grayscale :: Execute()
{
    if(inputA == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i;

    int index;
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();
    int inputIndex, outputIndex;
    Pixel *inputBuffer = inputA->getBuffer();
    Pixel *outputBuffer = output.getBuffer();
    output.ResetSize(outputW, outputH);


    for(i = 0; i < outputH * outputW; i++)
    {
        int grayval = inputBuffer[i].r/5 + inputBuffer[i].g/2 + inputBuffer[i].b/4;
        outputBuffer[i].r = (unsigned char) grayval;
        outputBuffer[i].g = (unsigned char) grayval;
        outputBuffer[i].b = (unsigned char) grayval;
    }
}

const char *Blur::FilterName()
{
    return "Blur";
}


void Blur :: Execute()
{
    if(inputA == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i, j;


    int index;
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();
    int inputIndex, outputIndex;
    Pixel *inputBuffer = inputA->getBuffer();
    Pixel *outputBuffer = output.getBuffer();
    output.ResetSize(outputW, outputH);

   unsigned char r1, r2, r3, g1,g2, g3, b1,b2,b3;

    for(i = 0; i < outputH; i++)
    {
        for(j = 0; j < outputW; j++)
        {
            index = i * outputW + j;
            if(i == 0 || i ==(outputH-1) || j == 0 || j == (outputW-1))

            {

                outputBuffer[index] = inputBuffer[index];
            }
            else
            {
                outputBuffer[index].r =  inputBuffer[(i-1)*outputW+j-1].r/8 +
                                            inputBuffer[(i-1)*outputW+j].r/8 +
                                            inputBuffer[(i-1)*outputW+j+1].r/8 +
                                            inputBuffer[i*outputW+j-1].r/8 +
                                            inputBuffer[i*outputW+j+1].r/8 +
                                            inputBuffer[(i+1)*outputW+j-1].r/8 +
                                            inputBuffer[(i+1)*outputW+j].r/8 +
                                            inputBuffer[(i+1)*outputW+j+1].r/8;

                outputBuffer[index].g =  inputBuffer[(i-1)*outputW+j-1].g/8 +
                                            inputBuffer[(i-1)*outputW+j].g/8 +
                                            inputBuffer[(i-1)*outputW+j+1].g/8 +
                                            inputBuffer[i*outputW+j-1].g/8 +
                                            inputBuffer[i*outputW+j+1].g/8 +
                                            inputBuffer[(i+1)*outputW+j-1].g/8 +
                                            inputBuffer[(i+1)*outputW+j].g/8 +
                                            inputBuffer[(i+1)*outputW+j+1].g/8;

                outputBuffer[index].b =  inputBuffer[(i-1)*outputW+j-1].b/8 +
                                            inputBuffer[(i-1)*outputW+j].b/8 +
                                            inputBuffer[(i-1)*outputW+j+1].b/8 +
                                            inputBuffer[i*outputW+j-1].b/8 +
                                            inputBuffer[i*outputW+j+1].b/8 +
                                            inputBuffer[(i+1)*outputW+j-1].b/8 +
                                            inputBuffer[(i+1)*outputW+j].b/8 +
                                            inputBuffer[(i+1)*outputW+j+1].b/8;
            }
        }
    }
}

const char *Color::FilterName()
{
    return "Color";
}

Color :: Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
    width = w;
    height = h;
    red = r;
    green = g;
    blue = b;
}

void Color :: Execute()
{
    int i;

    output.ResetSize(width, height);
    Pixel *outputBuffer = output.getBuffer();

    for(i = 0; i < height * width; i++)
    {
        outputBuffer[i].r = red;
        outputBuffer[i].g = green;
        outputBuffer[i].b = blue;
    }
}



void CheckSum :: OutputCheckSum(const char *filename)
{
    int i;
    FILE *f_in;
    f_in = fopen(filename, "w");

    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;

    
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();
    Pixel *inputBuffer = inputA->getBuffer();


    for(i = 0; i < outputH * outputW; i++)
    {
        red = red + inputBuffer[i].r;
        green = green + inputBuffer[i].g;
        blue = blue + inputBuffer[i].b;
    }

    fprintf(f_in, "CHECKSUM: %d, %d, %d\n", red, green, blue);
    fclose(f_in);
}
