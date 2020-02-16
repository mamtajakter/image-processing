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
	 FILE *in;
	 in = fopen (filename, "rb");
   fscanf(in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
   fprintf(stderr, "Read Image size: %d x %d\n", img.w, img.h);
	 for (int r = 0; r < height; r++) {
		 for (int c = 0; c < width; c++) {
			 unsigned char red, green, blue;
			 fscanf(in, "%c%c%c", &red, &green, &blue);
		 	 img.buffer[r*width+c].r = red;
			 img.buffer[r*width+c].g = green;
			 img.buffer[r*width+c].b = blue;
		 }
	 }
	 fclose(in);
   return ;
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
  
  fprintf(stderr, "%s\n", "successfully opened file!");
	FILE *out = fopen (filename, "wb");
	fprintf(out, "%s\n%d %d\n%d\n", "P6", img.w, img.h, img.mv);
  fprintf(stderr, "Write Image size: %d x %d\n", img.w, img.h);
	for (int r = 0; r < img.h; r++) {
		for (int c = 0; c < img.w; c++) {
			int pix_id = r*(img.w)+c;
			fprintf(out, "%c%c%c", img.buffer[pix_id].r
                 , img.buffer[pix_id].g
                 , img.buffer[pix_id].b);
		}
	}
	fclose(out);
  return;
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
