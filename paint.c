#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <stdint.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (640)

int main() {
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
    printf("Error initialising SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window* win = SDL_CreateWindow("LEGENDS OF ART",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  if (!win) {
    printf("Error creating window: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
  
  if (!rend) {
    printf("Error creating renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 1;
  }

  SDL_Event e;
  int quit = 0;

  SDL_Texture* tex = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WINDOW_WIDTH, WINDOW_HEIGHT);

  uint32_t* pixels = malloc(WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(uint32_t));
 
  uint32_t blue = (255 << 24) | (55 << 16) | (55 << 8) | 255;
  uint32_t gold = (255 << 24) | (255 << 16) | (204 << 8) | 0;
  /* (alpha << 24) | (red << 16) | (green << 8) | blue */

  memset(pixels, 192, WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(uint32_t));

  while (!quit){
    while (SDL_PollEvent(&e)){
 
      if (e.type == SDL_QUIT){
            quit = 1;
      }

      int mouse_x, mouse_y;
      int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

      if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        pixels[ (mouse_y - 1) * WINDOW_WIDTH + mouse_x - 1] = blue;
        pixels[ (mouse_y - 1) * WINDOW_WIDTH + mouse_x] = blue;
        pixels[ (mouse_y - 1) * WINDOW_WIDTH + mouse_x + 1] = blue;
        pixels[mouse_y * WINDOW_WIDTH + mouse_x - 1] = blue;
        pixels[mouse_y * WINDOW_WIDTH + mouse_x] = blue;
        pixels[mouse_y * WINDOW_WIDTH + mouse_x + 1] = blue;
        pixels[ (mouse_y + 1) * WINDOW_WIDTH + mouse_x - 1] = blue;
        pixels[ (mouse_y + 1) * WINDOW_WIDTH + mouse_x] = blue;
        pixels[ (mouse_y + 1) * WINDOW_WIDTH + mouse_x + 1] = blue;
      } else if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
        pixels[ (mouse_y - 1) * WINDOW_WIDTH + mouse_x - 1] = gold;
        pixels[ (mouse_y - 1) * WINDOW_WIDTH + mouse_x] = gold;
        pixels[ (mouse_y - 1) * WINDOW_WIDTH + mouse_x + 1] = gold;
        pixels[mouse_y * WINDOW_WIDTH + mouse_x - 1] = gold;
        pixels[mouse_y * WINDOW_WIDTH + mouse_x] = gold;
        pixels[mouse_y * WINDOW_WIDTH + mouse_x + 1] = gold;
        pixels[ (mouse_y + 1) * WINDOW_WIDTH + mouse_x - 1] = gold;
        pixels[ (mouse_y + 1) * WINDOW_WIDTH + mouse_x] = gold;
        pixels[ (mouse_y + 1) * WINDOW_WIDTH + mouse_x + 1] = gold;

      }

      SDL_UpdateTexture(tex, NULL, pixels, WINDOW_WIDTH * sizeof(uint32_t));
      SDL_RenderClear(rend);
      SDL_RenderCopy(rend, tex, NULL, NULL);

      SDL_RenderPresent(rend);
    }
  }

  free(pixels);
  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
