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

//   char magicNum[128];
//   int width, height, maxval;
//   FILE *f_in = fopen (filename, "rb");
//   fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
//
//
//
//   // Image *img;
//
// // c is width & r is height
//   // img = (Image *) malloc(sizeof(Pixel)*width*height);
//   img.w = width;
//   img.h = height;
//   img.mv = maxval;
//   img.buffer = (Pixel *) malloc(sizeof(Pixel)*width*height);
//
//   fread(img.buffer, sizeof(Pixel), width*height, f_in);
//
//   fclose(f_in);


   char magicNum[128];
   int width, height, maxval;
	 FILE *f_in= fopen (filename, "rb");
   fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

   unsigned char rr, gg, bb;

	 for (int i = 0; i < height; i++)
		 for (int j = 0; j < width; j++) {

			 fscanf(f_in, "%c%c%c", &rr, &gg, &bb);

		 	 img.buffer[i * width + j].r = rr;
			 img.buffer[i * width + j].g = gg;
			 img.buffer[i * width + j].b = bb;
		 }


	 fclose(f_in);
}


void WriteImage(char *filename, Image &img )
{
  // FILE *f_out = fopen(filename, "wb");
  //
  // fprintf (f_out, "P6\n");// first line "P6"
  // fprintf (f_out, "%d %d\n", img->w, img->h);// second line "1786 1344"
  // fprintf (f_out, "%d\n", img->mv);// third line "255"
  //
  // fwrite(img->buffer, sizeof(Pixel),  img->w * img->h, f_out);// write the entre image
  // fclose(f_out);

	FILE *f_out = fopen (filename, "wb");
  
  fprintf (f_out, "P6\n");// first line "P6"
  fprintf (f_out, "%d %d\n", img.w, img.h);// second line "1786 1344"
  fprintf (f_out, "%d\n", img.mv);// third line "255"

	for (int i = 0; i < img.h; i++)
		for (int j = 0; j < img.w; j++)
			fprintf(f_out, "%c%c%c", img.buffer[i*(img.w)+j].r, img.buffer[i*(img.w)+j].g, img.buffer[i*(img.w)+j].b);




	fclose(f_out);
}

Image *
YellowDiagonal(Image *input)
{
  // changing all diagonal pixel color to yellow
  for (int i = 0; i<input->w; i++)
      for (int j=0; j<input->h; j++)
          if (i==j)
          {
              input->buffer[i * input->w +j].r = 255;
              input->buffer[i * input->w +j].g = 255;
              input->buffer[i * input->w +j].b = 0;
          }
  return input;
}

// int main(int argc, char *argv[])
// {
//   /* Read an image, apply yellow diagonal to it, then write */
//   Image *img;
//   img = ReadImage(argv[1]);
//   YellowDiagonal(img);
//   WriteImage(img, argv[2]);
//
//   return 0;
//
// }
