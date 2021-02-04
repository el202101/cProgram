
#include "image-dither.h"
#include <stdio.h>
#include "round.h"

void update_grey_scale(struct image *img, int x, int y, int num, int denom, int error, int width, int height) {
  if ((x >= width) || (x < 0) || (y < 0) || (y >= height)) {
    return;
  }
  int grey =  image_get_pixel(img, x, y);
  int d_error = (div_round((num * error), denom));
  //  printf("e=%d, de=%d, x=%d, y-%d, num=%d, denom=%d, g=%d\n", error, d_error, x, y, num, denom,grey);
  d_error = d_error + grey;
  //printf("%d\n", d_error);
  if (d_error < 0) {
    d_error = 0;
  }
  if (d_error > 255) {
    d_error = 255;
  }
  /*  printf("e=%d, de=%d, x=%d, y-%d, num=%d, denom=%d, g=%d\n", error, d_error, x, y, num, denom,grey);
  printf("=========================================\n");
   printf("=========================================\n");
  if ((d_error < 0) || (d_error > 255)){
    printf("bad %d", d_error);
  } 
  else */
  image_set_pixel(img, x, y, d_error);
}

void dither(struct image *img, int x, int y, int grey) {
  int x1, x2, x3, x4, y1, y2, y3, y4;
  int error = 0;
  int width = image_get_width(img);
  int height = image_get_height(img);
  x1 = x + 1;
  y1 = y;
  x2 = x - 1;
  y2 = y + 1;
  x3 = x;
  y3 = y + 1;
  x4 = x + 1;
  y4 = y + 1;
  if (grey <= 127) {
    error = grey;
  }
  else {
    error = grey - 255;
  }
  update_grey_scale(img, x1, y1, 7, 16, error, width, height);
  update_grey_scale(img, x2, y2, 3, 16, error, width, height);
  update_grey_scale(img, x3, y3, 5, 16, error, width, height);
  update_grey_scale(img, x4, y4, 1, 16, error, width, height);
  if (grey <= 127) {
    //    printf("x=%d, y=%d\n", x, y);
    image_set_pixel(img, x, y, 0);
  }
  else {
    //    printf("**x=%d, **y=%d\n", x, y);
    image_set_pixel(img, x, y, 255);
  }
}

void image_print1(struct image *img) {
  //  int image_get_pixel(const struct image *img, int x, int y);
  // int image_get_width(const struct image *img);
  // int image_get_height(const struct image *img);
  int width;
  int height;
  int grey;
  int x = 0;
  int y = 0;
  width = image_get_width(img);
  // printf("**%d ", width);
  height = image_get_height(img);
  //  printf("%d\n", height);
  for (;!(y > (height - 1));) {
    x = 0;
    for (;!(x > (width - 1));) {
      grey = image_get_pixel(img, x, y);
      //  printf("g=%d, x=%d, y=%d\n", grey, x, y);
      dither(img, x, y, grey);
      ++x;
    }
    //  printf("\n");
    ++y;
  }
}

void image_dither(struct image *img) {

  image_print1(img);
}
