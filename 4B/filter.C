#include<stdio.h>
#include<stdlib.h>

#include "filter.h"
// #include "image.h"

Filter::Filter()
{
   // output.setSource(this);
}

Filter::~Filter()
{
   ;
}

void Filter::Update()
{
   if (inputA != NULL)
        inputA->Update();
      
   if (inputB != NULL)
       inputB->Update();
    
    Execute();

    //leak-free
    if (inputA)
        inputA->BufferClean();
    if (inputB)
        inputB->BufferClean();

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



void Shrinker::Execute()
{

  int outputH= inputA->getHeight()/2;
  int outputW= inputA->getWidth()/2;
  int inputIndex, outputIndex;

  output.ResetSize(outputW, outputH);

  Pixel *inputBuffer = inputA->getBuffer();
  Pixel *outputBuffer = output.getBuffer();

  for (int i = 0; i < outputH; i++)
    for (int j = 0; j < outputW; j++){

        inputIndex = i*2 * (inputA->getWidth()) + j*2;
        outputIndex = i * outputW + j;

        outputBuffer[outputIndex] = inputBuffer[inputIndex];
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


void LRCombine::Execute()
{

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

void TBCombine::Execute()
{

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
    this->factor = f;
}


double Blender::GetFactor(){
  return this->factor;
}


void Blender::Execute()
{

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
