/**************
 * FastImgDict
 **************/

#include<stdio.h>
#include<stdlib.h>
#include<png.h>

int main(int argc, char *argv[])
{
  char sig[8];

  FILE* fp = fopen("data/T03.png", "rb");
  if (!fp) {
    fprintf(stderr, "Failed to open image file\n");
    exit(2);
  }

  fread(sig, 1, 8, fp);

  return 0;
}
