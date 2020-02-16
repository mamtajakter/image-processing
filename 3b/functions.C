#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <image.h>
// void ImageAllocator() {
//  pixel = malloc(width*height*sizeof(Pixel));
//  int c,r; // if the image is 1024*768 size, width= 1024 and height = 768 then columns= width, rows = height, so the indexing formula is r*1024+c
// }


void ReadImage(char *filename, Image &img)
{
/* These lines are useful:
 * char magicNum[128];
 * int width, height, maxval;
 * fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
 * where f_in is the name of the input FILE.
 */

   char magicNum[128];
   int width, height, maxval;
	 FILE *f_in= fopen (filename, "rb");
   fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

   unsigned char rr, gg, bb;
   int index;

	 for (int i = 0; i < height; i++)
		 for (int j = 0; j < width; j++) {

			 fscanf(f_in, "%c%c%c", &rr, &gg, &bb);
       index=i * width + j;

		 	 img.buffer[index].r = rr;
			 img.buffer[index].g = gg;
			 img.buffer[index].b = bb;
		 }


	 fclose(f_in);

   // printf("reading done");
}


void WriteImage(char *filename, Image &img )
{


	FILE *f_out = fopen (filename, "wb");

  fprintf (f_out, "P6\n");// first line "P6"
  fprintf (f_out, "%d %d\n", img.w, img.h);// second line "1786 1344"
  fprintf (f_out, "%d\n", img.mv);// third line "255"

  int index;
	for (int i = 0; i < img.h; i++)
		for (int j = 0; j < img.w; j++){

       index=i * img.w + j;
			fprintf(f_out, "%c%c%c", img.buffer[index].r, img.buffer[index].g, img.buffer[index].b);
    }



	fclose(f_out);
     // printf("writing done");
}

// Image *
// YellowDiagonal(Image *input)
// {
//   // changing all diagonal pixel color to yellow
//   for (int i = 0; i<input->w; i++)
//       for (int j=0; j<input->h; j++)
//           if (i==j)
//           {
//               input->buffer[i * input->w +j].r = 255;
//               input->buffer[i * input->w +j].g = 255;
//               input->buffer[i * input->w +j].b = 0;
//           }
//   return input;
// }

void HalfSize(Image &input, Image &output )
{


  // unsigned char rr, gg, bb;
  int outputH= input.h/2;
  int outputW= input.w/2;
  int inputIndex, outputIndex;

  Pixel *pixel = (Pixel *)malloc(outputW*outputH*sizeof(Pixel));

  for (int i = 0; i < outputH; i++)
    for (int j = 0; j < outputW; j++){
        inputIndex = i*2 * (input.w) + j*2;
        outputIndex = i * outputW + j;

      pixel[outputIndex] = input.buffer[inputIndex];
    }

  Image *out = new Image(pixel, outputW, outputH, input.mv);
  output = *out;

     // printf("halfsize done");

}

void LeftRightCombine(Image &inputA, Image &inputB, Image &output )
{


  // unsigned char rr, gg, bb;
  int i, j;

  int outputH= inputA.h;
  int outputW= inputA.w+ inputB.w;
  int inputIndex, outputIndex;

  Pixel *pixel = (Pixel *)malloc(outputW*outputH*sizeof(Pixel));

  for ( i = 0; i < outputH; i++){
    for ( j = 0; j < inputA.w; j++){
        inputIndex = i * inputA.w + j;
        outputIndex = i * outputW + j;
        pixel[outputIndex] = inputA.buffer[inputIndex];
    }

}

for ( i = 0; i < outputH; i++){
    for ( j = inputA.w; j < outputW; j++){
        inputIndex = i * inputB.w + (j-inputA.w);
        outputIndex = i * outputW + j;
        pixel[outputIndex] = inputB.buffer[inputIndex];
    }
}

        Image *out = new Image(pixel, outputW, outputH, inputA.mv);
        output = *out;

        // printf("leftrightcombine done");



}


  void TopBottomCombine(Image &inputA, Image &inputB, Image &output)
  {
    // unsigned char rr, gg, bb;
    int i, j;
    int outputH= inputA.h+inputB.h;
    int outputW= inputA.w;
    int inputIndex, outputIndex;

    Pixel *pixel = (Pixel *)malloc(outputW*outputH*sizeof(Pixel));

    for ( i = 0; i < inputA.h; i++){
      for ( j = 0; j < outputW; j++){
            inputIndex = i * inputA.w + j;
            outputIndex = i * outputW + j;
            pixel[outputIndex] = inputA.buffer[inputIndex];

      }
    }


    for ( i = inputA.h; i < outputH; i++){
      for ( j = 0; j < outputW; j++){
          inputIndex = (i-inputA.h) * inputA.w + j;
          outputIndex = i * outputW + j;
          pixel[outputIndex] = inputB.buffer[inputIndex];
  }
}
          Image *out = new Image(pixel, outputW, outputH, inputA.mv);
          output = *out;

          // printf("leftrightcombine done");


  }


void Blend(Image &inputA, Image &inputB, double factor, Image &output)
  {

    int index;
    int outputH= inputA.h;
    int outputW= inputA.w;

    Pixel *pixel = (Pixel *)malloc(outputW*outputH*sizeof(Pixel));

    for (int i = 0; i < outputH; i++){
      for (int j = 0; j < outputW; j++) {

        index = i*outputW + j;

        Pixel pixelA = inputA.buffer[index];
        Pixel pixelB = inputB.buffer[index];

        pixel[index].r = factor*(pixelA).r + (1 - factor)*(pixelB).r;
        pixel[index].g = factor*(pixelA).g + (1 - factor)*(pixelB).g;
        pixel[index].b = factor*(pixelA).b + (1 - factor)*(pixelB).b;
      }
    }

    Image *out = new Image(pixel, outputW, outputH, inputA.mv);
    output = *out;
  }
