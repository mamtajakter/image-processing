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
    if(inputA->getWidth() != inputB->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), inputA->getWidth(),inputB->getWidth());
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
