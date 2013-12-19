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
  static png_structp png_ptr;
  static png_infop info_ptr;
  png_byte color_type;
  png_byte bit_depth;

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

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if( !png_ptr) {
    fprintf(stderr, "Couldn't allocate memory for PNG read struct\n");
    exit(2);
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    fprintf(stderr, "Couldn't get info ptr\n");
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    exit(2);
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    fprintf(stderr, "Error during init\n");
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    exit(2);
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);
  
  png_read_info(png_ptr, info_ptr);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);

  printf("Read PNG %dx%d\n", width, height);

  



  return 0;
}
