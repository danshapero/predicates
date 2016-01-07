
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <png.h>


typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} pixel_t;

typedef struct {
  pixel_t * pixels;
  size_t width;
  size_t height;
} bitmap_t;

static
pixel_t * pixel_at(const bitmap_t * bitmap, size_t x, size_t y)
{
  return bitmap->pixels + bitmap->width * y + x;
}


static
int save_png_to_file(const bitmap_t * bitmap, const char * filename)
{
  FILE * fp;
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;
  png_byte ** row_pointers = NULL;
  int status = -1;
  int pixel_size = 3;
  int depth = 8;

  fp = fopen(filename, "wb");
  if (!fp) goto fopen_failed;

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (png_ptr == NULL) goto png_create_write_struct_failed;

  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL) goto png_create_info_struct_failed;

  png_set_IHDR(png_ptr, info_ptr, bitmap->width, bitmap->height, depth,
               PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

  row_pointers = png_malloc(png_ptr, bitmap->height * sizeof(png_byte *));
  for (size_t y = 0; y < bitmap->height; ++y) {
    png_byte * row =
      png_malloc(png_ptr, sizeof(uint8_t) * bitmap->width * pixel_size);
    row_pointers[y] = row;
    for (size_t x = 0; x < bitmap->width; ++x) {
      pixel_t * pixel = pixel_at(bitmap, x, y);
      *row++ = pixel->red;
      *row++ = pixel->green;
      *row++ = pixel->blue;
    }
  }

  png_init_io(png_ptr, fp);
  png_set_rows(png_ptr, info_ptr, row_pointers);
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  status = 0;

  for (size_t y = 0; y < bitmap->height; ++y) png_free(png_ptr, row_pointers[y]);
  png_free(png_ptr, row_pointers);

 png_create_info_struct_failed:
  png_destroy_write_struct(&png_ptr, &info_ptr);
 png_create_write_struct_failed:
  fclose(fp);
 fopen_failed:
  return status;
}


static
bitmap_t matrix_to_bitmap(const size_t nx, const size_t ny, const double * A)
{
  bitmap_t bm =
    {.width = nx, .height = ny, .pixels = calloc(sizeof(pixel_t), nx * ny)};

  for (size_t i = 0; i < ny; ++i) {
    for (size_t j = 0; j < nx; ++j) {
      pixel_t * pixel = pixel_at(&bm, j, ny - i - 1);
      const double a = A[nx * i + j];
      pixel->red = 255 * (a > 0);
      pixel->blue = 255 * (a < 0);
    }
  }

  return bm;
}


int matrix_to_png(const char * filename,
                  const size_t nx,
                  const size_t ny,
                  const double * A)
{
  bitmap_t bitmap = matrix_to_bitmap(nx, ny, A);
  const int success = save_png_to_file(&bitmap, filename);
  free(bitmap.pixels);
  return success;
}
