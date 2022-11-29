#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (960)

#define SPEED (300)

int main() {
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
    printf("Error initialising SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window* win = SDL_CreateWindow("black pepper",
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

  SDL_Surface* surface = IMG_Load("/resources/flowers_of_atuan.png");
  if (!surface) {
    printf("Error creating surface: %s\n", SDL_GetError());
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 1;
  }

  SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
  SDL_FreeSurface(surface);

  if (!tex) {
    printf("Error creating texture: %s\n", SDL_GetError());
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 1;
  }
  
  SDL_Rect dest;
  SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
//  dest.w /= 4;
//  dest.h /= 4;

  float x_pos = (WINDOW_WIDTH - dest.w) / 2;
  float y_pos = (WINDOW_HEIGHT - dest.h) / 2;
  float x_vel = 0;
  float y_vel = 0;

  SDL_Event e;
  int quit = 0;
  while (!quit){
    while (SDL_PollEvent(&e)){
 
      if (e.type == SDL_QUIT){
            quit = 1;
      }

      int mouse_x, mouse_y;
      int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

      int target_x = mouse_x - dest.w / 2;
      int target_y = mouse_y - dest.h / 2;
      float delta_x = target_x - x_pos;
      float delta_y = target_y - y_pos;
      float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

      if (distance < 5) {
        x_vel = y_vel = 0;
      } else {
        x_vel = delta_x * SPEED / distance;
        y_vel = delta_y * SPEED / distance;
      }

      if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        x_vel = -x_vel;
        y_vel = -y_vel;
      }

      x_pos += x_vel / 60;
      y_pos += y_vel / 60;

      if (x_pos <= 0) x_pos = 0;
      if (y_pos <= 0) y_pos = 0;
      if (x_pos >= WINDOW_WIDTH - dest.w) x_pos = WINDOW_WIDTH - dest.w;
      if (y_pos >= WINDOW_HEIGHT - dest.h) y_pos = WINDOW_HEIGHT - dest.h;

      dest.y = (int) y_pos;
      dest.x = (int) x_pos;

      SDL_SetRenderDrawColor(rend, 55, 55, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(rend);
      SDL_RenderCopy(rend, tex, NULL, &dest);

      SDL_SetRenderDrawColor(rend, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawLine(rend, 320, 200, 300, 240);
      SDL_RenderDrawLine(rend, 300, 240, 340, 240);
      SDL_RenderDrawLine(rend, 340, 240, 320, 200);

      SDL_RenderPresent(rend);
      SDL_Delay(1000/60);
    }
  }

  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
