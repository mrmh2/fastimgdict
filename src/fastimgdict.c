/**************
 * FastImgDict
 **************/

#include<stdio.h>
#include<stdlib.h>
#include<png.h>

int main(int argc, char *argv[])
{
  char sig[8];
  unsigned long width, height;

  FILE* fp = fopen("data/T03.png", "rb");
  if (!fp) {
    fprintf(stderr, "Failed to open image file\n");
    exit(2);
  }

  fread(sig, 1, 8, fp);
  if (!png_check_sig(sig, 8)) {
    fprintf(stderr, "File is not a valid PNG file\n");
    exit(2);
  }



  return 0;
}
