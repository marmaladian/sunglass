#ifndef SG_DRAW
#define SG_DRAW

void sg_draw_point(unsigned int* pixels, int width, int height, sg_vec2i vec, unsigned int colour);
void sg_draw_line(unsigned int* pixels, int width, int height, sg_vec2i start, sg_vec2i end, unsigned int colour);
#endif
