//
// Created by Mamtaj Akter on 2020-03-07.
//

#include<stdio.h>
#include<stdlib.h>

#include "filter.h"
#include "logging.h"

Filter::Filter()
{
    ;
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
	if (numOfCalls > 2000){
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
    int inputIndex, outputIndex;
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();

    output.ResetSize(outputW, outputH);

    Pixel *inputBuffer = inputA->getBuffer();
    Pixel *outputBuffer = output.getBuffer();


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
    int inputIndex, outputIndex;
    int outputW= inputA->getHeight();
    int outputH= inputA->getWidth();

    output.ResetSize(outputW, outputH);

    Pixel *inputBuffer = inputA->getBuffer();
    Pixel *outputBuffer = output.getBuffer();

    for(i = 0; i < outputH; i++)
        {
            for(j= 0; j < outputW; j++)
            {
                inputIndex = (outputW - 1 - j) * outputH + i;
                outputIndex= i * outputW + j;
                outputBuffer[outputIndex] = inputBuffer[inputIndex];
            }
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
    int i,j;

    
    int index;
    int inputIndex, outputIndex;
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();

    output.ResetSize(outputW, outputH);

    Pixel *inputABuffer = inputA->getBuffer();
    Pixel *inputBBuffer = inputB->getBuffer();
    Pixel *outputBuffer = output.getBuffer();

    for(i = 0; i < outputH; i++)
        for (j=0; j< outputW; j++)
    {
        index = i* outputW +j;
        
        if (inputABuffer[index].r < inputBBuffer[index].r)
            outputBuffer[index].r = 0;
        else
            outputBuffer[index].r = inputABuffer[index].r - inputBBuffer[index].r;

        if (inputABuffer[index].g < inputBBuffer[index].g)
            outputBuffer[index].g = 0;
        else
            outputBuffer[index].g = inputABuffer[index].g - inputBBuffer[index].g;

        if (inputABuffer[index].b < inputBBuffer[index].b)
            outputBuffer[index].b = 0;
        else
            outputBuffer[index].b = inputABuffer[index].b - inputBBuffer[index].b;
       
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

    int i,j;
    int index;
    int inputIndex, outputIndex;
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();

    output.ResetSize(outputW, outputH);
    Pixel *inputBuffer = inputA->getBuffer();
    Pixel *outputBuffer = output.getBuffer();
    

    for(i = 0; i < outputH; i++)
    
        for ( j=0; j< outputW; j++)
    
    {
        index = i * outputW + j;

        int grayval = inputBuffer[index].r/5 + inputBuffer[index].g/2 + inputBuffer[index].b/4;

        outputBuffer[index].r = (unsigned char) grayval;
        outputBuffer[index].g = (unsigned char) grayval;
        outputBuffer[index].b = (unsigned char) grayval;
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
    int x1,x2,x3,x4,x5,x6,x7,x8;
    int inputIndex, outputIndex;
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();

    output.ResetSize(outputW, outputH);
    Pixel *inputBuffer = inputA->getBuffer();
    Pixel *outputBuffer = output.getBuffer();

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
                x1 = (i-1)*outputW+j-1;
                x2 = (i-1)*outputW+j;
                x3 = (i-1)*outputW+j+1;
                x4 = i*outputW+j-1;
                x5 = i*outputW+j+1;
                x6 = (i+1)*outputW+j-1;
                x7 = (i+1)*outputW+j;
                x8 = (i+1)*outputW+j+1;

                outputBuffer[index].r =  inputBuffer[x1].r/8 + inputBuffer[x2].r/8 +
                                        inputBuffer[x3].r/8 + inputBuffer[x4].r/8 +
                                        inputBuffer[x5].r/8 + inputBuffer[x6].r/8 +
                                        inputBuffer[x7].r/8 + inputBuffer[x8].r/8;

                outputBuffer[index].g =  inputBuffer[x1].g/8 + inputBuffer[x2].g/8 +
                                        inputBuffer[x3].g/8 + inputBuffer[x4].g/8 +
                                        inputBuffer[x5].g/8 + inputBuffer[x6].g/8 +
                                        inputBuffer[x7].g/8 + inputBuffer[x8].g/8;


                outputBuffer[index].b =  inputBuffer[x1].b/8 + inputBuffer[x2].b/8 +
                                        inputBuffer[x3].b/8 + inputBuffer[x4].b/8 +
                                        inputBuffer[x5].b/8 + inputBuffer[x6].b/8 +
                                        inputBuffer[x7].b/8 + inputBuffer[x8].b/8;

                
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
    int i,j;
    int index;
    output.ResetSize(width, height);

    Pixel *outputBuffer = output.getBuffer();
   

    for(i = 0; i < height; i++)
        for (j=0; j< width; j++)
        {
            index = i * width + j;

            outputBuffer[index].r = red;
            outputBuffer[index].g = green;
            outputBuffer[index].b = blue;
        }

    
}

const char *CheckSum :: SinkName()
{
    return "CheckSum";
}

void CheckSum :: OutputCheckSum(const char *filename)
{
    int i,j;
    FILE *f_in;
    f_in = fopen(filename, "w");

    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;

    int index;
    int outputH= inputA->getHeight();
    int outputW= inputA->getWidth();
    Pixel *inputBuffer = inputA->getBuffer();

    for(i = 0; i < outputH ; i++)
        for (j=0; j< outputW; j++)
        {
            index = i * outputW + j;

            red = red + inputBuffer[index].r;
            green = green + inputBuffer[index].g;
            blue  = blue + inputBuffer[index].b;
        }

   

    fprintf(f_in, "CHECKSUM: %d, %d, %d\n", red, green, blue);
    fclose(f_in);
}
