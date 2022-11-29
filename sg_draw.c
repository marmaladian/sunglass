#include "sg_vectors.h"
#include "sg_draw.h"
#include <stdio.h>
#include <stdlib.h>

void sg_draw_point(unsigned int* pixels, int width, int height, sg_vec2i vec, unsigned int colour) {
  if (vec.x >= 0 && vec.x < width && vec.y >= 0 && vec.y < height) {
    pixels[(int) vec.x + (int) vec.y * width] = colour;
  }
}

//  TODO could make it so pixels is set as a global, and not passed to all the functions. like opengl functions?
//  no checking that points are within image space.
void sg_draw_line2(unsigned int* pixels, int width, int height, sg_vec2i start_, sg_vec2i end_, unsigned int colour) {
  if (start_.x == end_.x && start_.y == end_.y) {
    sg_draw_point(pixels, width, height, start_, colour);
  }

  sg_vec2i start = start_;
  sg_vec2i end = end_;

  if (start_.x < end_.x) {
    start = end_;
    end = start_;
  }

  int dx = end.x - start.x;
  int dy = end.y - start.y;

  if (dx > dy) {
  /* if dx > dy, then slope runs horizontally */
    float fault = dx/2.0f;
    int iy = 0;
    for (int ix = 0; ix < dx; ix++) {
      fault -= dy;
      if (fault < 0) {
        iy++;
        fault += dx;
      }
      sg_vec2i p = { start.x + ix, start.y + iy };
      sg_draw_point(pixels, width, height, p, colour);
    }
  } else {
    float fault = dy/2.0f;
    int ix = 0;
    for (int iy = 0; iy < dy; iy++) {
      fault -= dx;
      if (fault < 0) {
        ix++;
        fault += dy;
      }
      sg_vec2i p = { start.x + ix, start.y + iy };
      sg_draw_point(pixels, width, height, p, colour);
    }
  }
}

void sg_draw_line(unsigned int* pixels, int width, int height, sg_vec2i start, sg_vec2i end, unsigned int colour) {
  int x0 = start.x;
  int y0 = start.y;
  int x1 = end.x;
  int y1 = end.y;

  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  for (;;) {
    sg_vec2i p = { x0, y0 };
    sg_draw_point(pixels, width, height, p, colour);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}
