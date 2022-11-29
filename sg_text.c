#include "sg_text.h"

SDL_Texture* sg_charset_init(char* filename) {

  SDL_Surface* surface = IMG_Load(filename);
  if (!surface)
    printf("Error creating surface: %s\n", SDL_GetError());

  SDL_Texture* tex = SDL_CreateTextureFromSurface(render, surface);
  SDL_FreeSurface(surface);

  if (!tex)
    printf("Error creating texture: %s\n", SDL_GetError());
  return tex;  
}

SDL_Rect sg_atlas_rect(int index, int tile_width, int tile_height, int tiles_x, int tiles_y) {
  SDL_Rect tile = { 0, 0, tile_width, tile_height }; 
  if (index >= 0 && index < tiles_x * tiles_y) {
    int x = (index % tiles_x) * tile_width;
    int y = (index / tiles_y) * tile_height;
    tile.x = x;
    tile.y = y;
  }

  //printf("%i) %i, %i\n", index, tile.x, tile.y);
  return tile;
}

void sg_draw_tile(int index, SDL_Rect* dest, SDL_Texture* tex) {
  SDL_Rect tile_rect = sg_atlas_rect(index, 8, 8, 16, 16); 
  SDL_RenderCopy(render, tex, &tile_rect, dest);
}

void sg_draw_string(char* str, int x, int y, SDL_Texture* tex) {
  // change this to a bounding box later, with wrap/clip option
  int i = 0;
  do {
    SDL_Rect dest = { x + i * 8, y, 8, 8 };
    sg_draw_tile((int) str[i], &dest, tex); 
    i++;
  } while (str[i] != '\0');
}
