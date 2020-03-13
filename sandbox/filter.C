//
// Created by Mamtaj Akter on 2020-03-07.
//

#include<stdio.h>
#include<stdlib.h>

#include "filter.h"
#include "logging.h"
// #include "image.h"

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
//        inputA->Update();

    if (inputB != NULL){
        char msg[128];
        sprintf(msg, "%s: about to update input2", SourceName());
        Logger::LogEvent(msg);
        inputB->Update();
        sprintf(msg, "%s: done updating input2", SourceName());
        Logger::LogEvent(msg);
    }
//        inputB->Update();
    char msg[128];
    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);

}


// Shrinker::Shrinker(){

//       GetOutput()->setSource(this);
// };

// Shrinker::~Shrinker()
// {
//    ;
// }


// void  Shrinker::Update(){

//   if (GetInput() != NULL){

//       GetInput()->Update();

//       }

//  this->Execute();


// };

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


// LRCombine::LRCombine(){

//   GetOutput()->setSource(this);

// };

// LRCombine::~LRCombine(){

//   ;

// };

// void  LRCombine::Update(){

//   if (GetInput() != NULL){

//   GetInput()->Update();

//   }

//   if (GetInput2() != NULL){

//   GetInput2()->Update();

//   }

//   this->Execute();

// };
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
//    if(inputA->getWidth() != inputB->getWidth())
//    {
//        char msg[1024];
//        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), inputA->getWidth(),inputB->getWidth());
//        DataFlowException e(SinkName(), msg);
//        throw e;
//    }

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

// TBCombine::TBCombine(){

//   GetOutput()->setSource(this);

// };

// TBCombine::~TBCombine(){

//   ;

// };

// void  TBCombine::Update(){

//   if (GetInput() != NULL){

//   GetInput()->Update();

//   }

//   if (GetInput2() != NULL){

//   GetInput2()->Update();

//   }

//   this->Execute();

// };

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
//    if(inputA->getHeight() != inputB->getHeight())
//    {
//        char msg[1024];
//        sprintf(msg, "%s: heights must match: %d, %d", SinkName(), inputA->getHeight(),inputB->getHeight());
//        DataFlowException e(SinkName(), msg);
//        throw e;
//    }
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

// Blender::Blender(){

//   GetOutput()->setSource(this);

// };

// Blender::~Blender(){

//   ;

// };

// void  Blender::Update(){

//   if (GetInput() != NULL){

//   GetInput()->Update();

//   }

//   if (GetInput2() != NULL){

//   GetInput2()->Update();

//   }

//   this->Execute();

// };

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

    output.ResetSize(inputA->getWidth(), inputA->getHeight());


    for(i = 0; i < output.getHeight(); i++)
    {
        for(j = 0; j < output.getWidth(); j++)
        {
            output.getBuffer()[i * output.getWidth() + j] = inputA->getBuffer()[i * output.getWidth() + (output.getWidth() - 1 - j)];
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

    output.ResetSize(inputA->getHeight(), inputA->getWidth());


    for(i = 0; i < output.getHeight(); i++)
    {
        for(j= 0; j < output.getWidth(); j++)
        {
            output.getBuffer()[i * output.getWidth() + j] = inputA->getBuffer()[(output.getWidth() - 1 - j) * output.getHeight() + i];
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
    int i;

    output.ResetSize(inputA->getWidth(), inputA->getHeight());


    for(i = 0; i < output.getHeight() * output.getWidth(); i++)
    {
        output.getBuffer()[i].r = (inputA->getBuffer()[i].r < inputB->getBuffer()[i].r) ? 0 : inputA->getBuffer()[i].r - inputB->getBuffer()[i].r;
        output.getBuffer()[i].g = (inputA->getBuffer()[i].g < inputB->getBuffer()[i].g) ? 0 : inputA->getBuffer()[i].g - inputB->getBuffer()[i].g;
        output.getBuffer()[i].b = (inputA->getBuffer()[i].b < inputB->getBuffer()[i].b) ? 0 : inputA->getBuffer()[i].b - inputB->getBuffer()[i].b;
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

    output.ResetSize(inputA->getWidth(), inputA->getHeight());


    for(i = 0; i < output.getHeight() * output.getWidth(); i++)
    {
        int val = inputA->getBuffer()[i].r/5 + inputA->getBuffer()[i].g/2 + inputA->getBuffer()[i].b/4;
        output.getBuffer()[i].r = (unsigned char) val;
        output.getBuffer()[i].g = (unsigned char) val;
        output.getBuffer()[i].b = (unsigned char) val;
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

    output.ResetSize(inputA->getWidth(), inputA->getHeight());


    for(i = 0; i < output.getHeight(); i++)
    {
        for(j = 0; j < output.getWidth(); j++)
        {
            if(i == 0 || i ==(output.getHeight()-1) || j == 0 || j == (output.getWidth()-1))
            {
                output.getBuffer()[i * output.getWidth() + j] = inputA->getBuffer()[i * output.getWidth() + j];
            }
            else
            {
                output.getBuffer()[i*output.getWidth()+j].r =  inputA->getBuffer()[(i-1)*output.getWidth()+j-1].r/8 +
                                                               inputA->getBuffer()[(i-1)*output.getWidth()+j].r/8 +
                                                               inputA->getBuffer()[(i-1)*output.getWidth()+j+1].r/8 +
                                                               inputA->getBuffer()[i*output.getWidth()+j-1].r/8 +
                                                               inputA->getBuffer()[i*output.getWidth()+j+1].r/8 +
                                                               inputA->getBuffer()[(i+1)*output.getWidth()+j-1].r/8 +
                                                               inputA->getBuffer()[(i+1)*output.getWidth()+j].r/8 +
                                                               inputA->getBuffer()[(i+1)*output.getWidth()+j+1].r/8;

                output.getBuffer()[i*output.getWidth()+j].g =  inputA->getBuffer()[(i-1)*output.getWidth()+j-1].g/8 +
                                                               inputA->getBuffer()[(i-1)*output.getWidth()+j].g/8 +
                                                               inputA->getBuffer()[(i-1)*output.getWidth()+j+1].g/8 +
                                                               inputA->getBuffer()[i*output.getWidth()+j-1].g/8 +
                                                               inputA->getBuffer()[i*output.getWidth()+j+1].g/8 +
                                                               inputA->getBuffer()[(i+1)*output.getWidth()+j-1].g/8 +
                                                               inputA->getBuffer()[(i+1)*output.getWidth()+j].g/8 +
                                                               inputA->getBuffer()[(i+1)*output.getWidth()+j+1].g/8;

                output.getBuffer()[i*output.getWidth()+j].b =  inputA->getBuffer()[(i-1)*output.getWidth()+j-1].b/8 +
                                                               inputA->getBuffer()[(i-1)*output.getWidth()+j].b/8 +
                                                               inputA->getBuffer()[(i-1)*output.getWidth()+j+1].b/8 +
                                                               inputA->getBuffer()[i*output.getWidth()+j-1].b/8 +
                                                               inputA->getBuffer()[i*output.getWidth()+j+1].b/8 +
                                                               inputA->getBuffer()[(i+1)*output.getWidth()+j-1].b/8 +
                                                               inputA->getBuffer()[(i+1)*output.getWidth()+j].b/8 +
                                                               inputA->getBuffer()[(i+1)*output.getWidth()+j+1].b/8;
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

    for(i = 0; i < height * width; i++)
    {
        output.getBuffer()[i].r = red;
        output.getBuffer()[i].g = green;
        output.getBuffer()[i].b = blue;
    }
}

//void Color::Update(){
//    char msg[128];
//
//    sprintf(msg, "%s: about to execute", SourceName());
//    Logger::LogEvent(msg);
//    Execute();
//    sprintf(msg, "%s: done executing", SourceName());
//    Logger::LogEvent(msg);
//}

void CheckSum :: OutputCheckSum(const char *filename)
{
    int i;
    FILE *f_in;
    f_in = fopen(filename, "w");

    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;

    for(i = 0; i < inputA->getHeight() * inputA->getWidth(); i++)
    {
        red += inputA->getBuffer()[i].r;
        green += inputA->getBuffer()[i].g;
        blue += inputA->getBuffer()[i].b;
    }

    fprintf(f_in, "CHECKSUM: %d, %d, %d\n", red, green, blue);
    fclose(f_in);
}
