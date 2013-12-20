/**************
 * FastImgDict
 **************/

#include<stdio.h>
#include<stdlib.h>
#include<png.h>
#include<vector>
#include<unordered_map>

typedef struct {
  int R;
  int G;
  int B;
} rgb_val;

rgb_val get_rgb_val(png_bytep* row_pointers, int x, int y)
{
  rgb_val rgb;

  int offset = x * 3;

  rgb.R = row_pointers[y][offset];
  rgb.G = row_pointers[y][offset + 1];
  rgb.B = row_pointers[y][offset + 2];

  return rgb;
}

unsigned long convert_rgb_val(rgb_val rgb)
{
  return 256 * 256 * rgb.R + 256 * rgb.G + rgb.B;
}

void load_png(const char *filename, png_structp* in_png_ptr, png_infop* in_info_ptr)
{
  /* load a PNG file */

  //png_const_bytep sig;
  png_structp png_ptr;
  png_infop info_ptr;

  FILE* fp = fopen(filename, "rb");
  if (!fp) {
    fprintf(stderr, "Failed to open image file\n");
    exit(2);
  }

  /*
  fread(sig, 1, 8, fp);
  if (!png_check_sig(sig, 8)) {
    fprintf(stderr, "File is not a valid PNG file\n");
    exit(2);
  }
  */

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
  //png_set_sig_bytes(png_ptr, 8);
  png_read_png(png_ptr, info_ptr, 0, NULL);

  *in_png_ptr = png_ptr;
  *in_info_ptr = info_ptr;
}

typedef struct {
  int x;
  int y;
} c2d;

int main(int argc, char** argv)
{

  unsigned long width, height;
  static png_structp png_ptr;
  static png_infop info_ptr;
  png_byte color_type;
  png_byte bit_depth;
  png_bytep* row_pointers;
  rgb_val rgb;
  unsigned long val;
  c2d current_xy;

  load_png("data/T13.png", &png_ptr, &info_ptr);
  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  row_pointers = png_get_rows(png_ptr, info_ptr);

  std::unordered_map <int, std::vector<c2d>> m;

  for (int y=0; y<height; y++) 
    for (int x=0; x<width; x++) {
      val = convert_rgb_val(get_rgb_val(row_pointers, x, y));
      current_xy.x = x;
      current_xy.y = y;
      if (!m.count(val)) {
	m[val] = std::vector<c2d>();
      } else {
	m[val].push_back(current_xy);
      }

    }

  for (auto kv : m) {
    printf("%d: %d\n", kv.first, kv.second.size());
  }


  return 0;
}
