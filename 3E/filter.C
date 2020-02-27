#include<stdio.h>
#include "filter.h"
#include<stdlib.h>

Filter::Filter(){
  ;
}

Filter::~Filter(){
  ;
}


Shrinker::Shrinker(){

	   GetOutput()->setSource(this);
};

Shrinker::~Shrinker(){

	   ;
};

void	Shrinker::Update(){
	if (getInput() != NULL){
	getInput()->Update();
	}
	this->Execute();

};

void Shrinker::Execute()
{

  int outputH= imageA->getHeight()/2;
  int outputW= imageA->getWidth()/2;
  int inputIndex, outputIndex;

  image.ResetSize(outputW, outputH);

  Pixel *inputBuffer = imageA->getBuffer();
  Pixel *outputBuffer = image.getBuffer();

  for (int i = 0; i < outputH; i++)
    for (int j = 0; j < outputW; j++){

        inputIndex = i*2 * (imageA->getWidth()) + j*2;
        outputIndex = i * outputW + j;

        outputBuffer[outputIndex] = inputBuffer[inputIndex];
    }

}


LRCombine::LRCombine(){
	GetOutput()->setSource(this);
};

LRCombine::~LRCombine(){
	;
};

void 	LRCombine::Update(){
	if (getInput() != NULL){
	getInput()->Update();
	}
	if (getInput2() != NULL){
	getInput2()->Update();
	}
	this->Execute();
};
void LRCombine::Execute()
{

    int i, j;

    int outputH= imageA->getHeight();
    int outputW= imageA->getWidth()+ imageB->getWidth();
    int inputIndex, outputIndex;

    image.ResetSize(outputW, outputH);

    Pixel *inputABuffer = imageA->getBuffer();
    Pixel *inputBBuffer = imageB->getBuffer();
    Pixel *outputBuffer = image.getBuffer();

    for ( i = 0; i < outputH; i++){
      for ( j = 0; j < imageA->getWidth(); j++){

          inputIndex = i * imageA->getWidth() + j;
          outputIndex = i * outputW + j;

          outputBuffer[outputIndex] = inputABuffer[inputIndex];
      }

    }

    for ( i = 0; i < outputH; i++){
      for ( j = imageA->getWidth(); j < outputW; j++){
          inputIndex = i * imageB->getWidth()+ (j-imageA->getWidth());
          outputIndex = i * outputW + j;
          outputBuffer[outputIndex] = inputBBuffer[inputIndex];
      }
    }


}


TBCombine::TBCombine(){
      	GetOutput()->setSource(this);

}
TBCombine::TBCombine(){
      	;

}

void 	TBCombine::Update(){
	if (getInput() != NULL){
	getInput()->Update();
	}
	if( getInput2() != NULL){
	getInput2()->Update();
	}
	this->Execute();
};

void TBCombine::Execute()
{

      int i, j;
      int outputH= imageA->getHeight()+imageB->getHeight();
      int outputW= imageA->getWidth();
      int inputIndex, outputIndex;

      image.ResetSize(outputW, outputH);

      Pixel *inputABuffer = imageA->getBuffer();
      Pixel *inputBBuffer = imageB->getBuffer();
      Pixel *outputBuffer = image.getBuffer();


      for ( i = 0; i < imageA->getHeight(); i++){
        for ( j = 0; j < outputW; j++){

              inputIndex = i * imageA->getWidth()+ j;
              outputIndex = i * outputW + j;

              outputBuffer[outputIndex] = inputABuffer[inputIndex];

        }
      }


      for ( i = imageA->getHeight(); i < outputH; i++){
        for ( j = 0; j < outputW; j++){

            inputIndex = (i-imageA->getHeight()) * imageA->getWidth() + j;
            outputIndex = i * outputW + j;

            outputBuffer[outputIndex] = inputBBuffer[inputIndex];
    }
    }


}



Blender::Blender(){
	GetOutput()->setSource(this);
};
Blender::~Blender(){
	;
};

void 	Blender::Update(){
	if (getInput() != NULL){
	getInput()->Update();
	}
	if( getInput2() != NULL){
	getInput2()->Update();
	}
	this->Execute();
};


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
    int outputH= imageA->getHeight();
    int outputW= imageA->getWidth();

    image.ResetSize(outputW, outputH);

    Pixel *inputABuffer = imageA->getBuffer();
    Pixel *inputBBuffer = imageB->getBuffer();
    Pixel *outputBuffer = image.getBuffer();

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
