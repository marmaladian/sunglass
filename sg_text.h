#ifndef SG_TEXT
#define SG_TEXT
#include <SDL2/SDL_image.h>

extern SDL_Window *window;
extern SDL_Renderer *render;
extern SDL_Texture *display;

SDL_Texture* sg_charset_init(char* filename);
SDL_Rect sg_atlas_rect(int index, int tile_width, int tile_height, int tiles_x, int tiles_y);
void sg_draw_tile(int index, SDL_Rect* dest, SDL_Texture* tex);
void sg_draw_string(char* str, int x, int y, SDL_Texture* tex);
#endif
