/* sunglass
 * a software renderer
 *
 * https://benedicthenshaw.com/soft_render_sdl2.html
 * was helpful in writing this.
 *
 * https://en.wikipedia.org/wiki/Transformation_matrix
*/

#include "main.h"

#define VIRTUAL_WIDTH 300
#define VIRTUAL_HEIGHT 300
#define IMAGE_WIDTH 750
#define IMAGE_HEIGHT 750

#define CHARSET "/resources/8x8_ascii_v2.png"

sg_mat44 sg_matrix_camlookat(sg_vec3 from, sg_vec3 to) {

  sg_vec3 forward = sg_vec3_normalise(sg_vec3_sub(from, to));
  sg_vec3 right = sg_vec3_cross(sg_vec3_normalise(sg_vec3_new(0, 1, 0)), forward);
  sg_vec3 up = sg_vec3_cross(forward, right);

  sg_mat44 m;

  m.m[0][0] = right.x;
  m.m[1][0] = right.y;
  m.m[2][0] = right.z;
  m.m[3][0] = 0;
  m.m[0][1] = up.x;
  m.m[1][1] = up.y;
  m.m[2][1] = up.z;
  m.m[3][1] = 0;
  m.m[0][2] = forward.x;
  m.m[1][2] = forward.x;
  m.m[2][2] = forward.z;
  m.m[2][0] = 0;
  m.m[0][3] = from.x;
  m.m[1][3] = from.y;
  m.m[2][3] = from.z;
  m.m[3][3] = 1;
  
  return m;
}

sg_vec2i compute_pixel_coords(sg_vec3 p_world,
                              sg_mat44 cam_to_world,
                              float canvas_width,
                              float canvas_height,
                              int image_width,
                              int image_height) {
  sg_vec3 p_camera;
  sg_mat44 world_to_cam = sg_matrix_inverse(cam_to_world);
  p_camera = sg_matrix_mul_vec3(world_to_cam, p_world);

  sg_vec2f p_screen;
  p_screen.x = p_camera.x / -p_camera.z;
  p_screen.y = p_camera.y / -p_camera.z;

  // TODO this currently returns 0,0 but should return no point.
  if (fabsf(p_screen.x) > canvas_width || fabsf(p_screen.y) > canvas_height) return sg_vec2i_new(0,0);

  sg_vec2f p_NDC;
  p_NDC.x = (p_screen.x + canvas_width / 2) / canvas_width;
  p_NDC.y = (p_screen.y + canvas_height / 2) / canvas_height;

  sg_vec2i p_raster;
  p_raster.x = floor(p_NDC.x * image_width);
  p_raster.y = floor((1 - p_NDC.y) * image_height);

  /* 
  printf("world %.1f, %.1f, %.1f -> cam %.1f, %.1f, %.1f -> screen %.1f, %.1f -> NDC %.1f, %.1f -> raster %i, %i\n",
         p_world.x, p_world.y, p_world.z,
         p_camera.x, p_camera.y, p_camera.z,
         p_screen.x, p_screen.y,
         p_NDC.x, p_NDC.y,
         p_raster.x, p_raster.y);
  */

  return p_raster;
}

void sg_window_init() {
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("Sunglass",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      IMAGE_WIDTH, IMAGE_HEIGHT,
      0);

  render = SDL_CreateRenderer(window,
      -1, SDL_RENDERER_PRESENTVSYNC);

  SDL_RenderSetLogicalSize(render, VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
  SDL_RenderSetIntegerScale(render, 1);
  SDL_SetRenderDrawColor(render, SG_RGB255_WHITE, 255);
  SDL_RenderClear(render);

  display = SDL_CreateTexture(render,
      SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
      VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
}

void sg_draw_model(unsigned int* pixels, sg_model* model) {
  sg_vec3 from = { 0.0, 1, -1 };
  sg_vec3 to = { 0, 0, 0 };

  // TODO stop calculating this every time!
  sg_mat44 camera_to_world = sg_matrix_camlookat(from, to);

  /* get next tri */


  /* draw edges */
  for (int i = 0; i < model->num_tris; i += 3) {
    sg_vec3 o0 = model->verts[i];
    sg_vec3 o1 = model->verts[i+1];
    sg_vec3 o2 = model->verts[i+2];

    sg_vec2i v0 = compute_pixel_coords(model->verts[model->tris[i]], camera_to_world, 2, 2, VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    sg_vec2i v1 = compute_pixel_coords(model->verts[model->tris[i + 1]], camera_to_world, 2, 2, VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    sg_vec2i v2 = compute_pixel_coords(model->verts[model->tris[i + 2]], camera_to_world, 2, 2, VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    sg_draw_line(pixels, VIRTUAL_WIDTH, VIRTUAL_HEIGHT, v0, v1, SG_RGBA8888_NEWWH);
    sg_draw_line(pixels, VIRTUAL_WIDTH, VIRTUAL_HEIGHT, v1, v2, SG_RGBA8888_NEWWH);
    sg_draw_line(pixels, VIRTUAL_WIDTH, VIRTUAL_HEIGHT, v2, v0, SG_RGBA8888_NEWWH);


  }

  /* draw vertices */
  for (int i = 0; i < model->num_verts; i++) {
    sg_vec2i v = compute_pixel_coords(model->verts[i], camera_to_world, 2, 2, VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
    sg_draw_point(pixels, VIRTUAL_WIDTH, VIRTUAL_HEIGHT, v, SG_RGBA8888_RED);
  }

}

void sg_fill_pixels(unsigned int* pixels) {
  for (int x = 0; x < VIRTUAL_WIDTH; x++) {
    for (int y = 0; y < VIRTUAL_HEIGHT; y++) {
      sg_vec2i p = { x, y };
      sg_draw_point(pixels, VIRTUAL_WIDTH, VIRTUAL_HEIGHT, p, SG_RGBA8888_GREY);
    }
  }
}

void sg_pixels_update(unsigned int* pixels, sg_model*  model) {
  sg_fill_pixels(pixels);
  sg_draw_model(pixels, model);
}


// TODO removed these from fn because they were being assigned each loop,
//      but they should not be global either.
int rotate_cw = 0;
int rotate_ccw = 0;
int rotate_bf = 0;
int rotate_fb = 0;
int scale_up = 0;
int scale_down = 0;

sg_vec3 scale_up_vec = { 1.1, 1.1, 1.1 };
sg_vec3 scale_down_vec = { 1.0 / 1.1, 1.0 / 1.1, 1.0 / 1.1};
float rotate_deg = 1;

void sg_model_update(sg_model* model) {

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) exit(0);

    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_Q:
          scale_down = 1;
          break;
        case SDL_SCANCODE_E:
          scale_up = 1;
          break;
        case SDL_SCANCODE_A:
          rotate_ccw = 1;
          break;
        case SDL_SCANCODE_D:
          rotate_cw = 1;
          break;
        case SDL_SCANCODE_W:
          rotate_fb = 1;
          break;
        case SDL_SCANCODE_S:
          rotate_bf = 1;
          break;
        default:
          break;
      }
    }

    if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_Q:
          scale_down = 0;
          break;
        case SDL_SCANCODE_E:
          scale_up = 0;
          break;
        case SDL_SCANCODE_A:
          rotate_ccw = 0;
          break;
        case SDL_SCANCODE_D:
          rotate_cw = 0;
          break;
        case SDL_SCANCODE_W:
          rotate_fb = 0;
          break;
        case SDL_SCANCODE_S:
          rotate_bf = 0;
          break;
        default:
          break;
      }
    }
  }

  if (scale_up) {
    for (int i = 0; i < model->num_verts; i++) {
      sg_vec3 scaled_vec;
      scaled_vec = sg_vec3_scale(model->verts[i], scale_up_vec);
      model->verts[i] = scaled_vec;
    }
  }

  if (scale_down) {
    for (int i = 0; i < model->num_verts; i++) {
      sg_vec3 scaled_vec;
      scaled_vec = sg_vec3_scale(model->verts[i], scale_down_vec);
      model->verts[i] = scaled_vec;
    }
  }

  if (rotate_cw) {
    for (int i = 0; i < model->num_verts; i++) {
      sg_vec3 rotated_vec;
      rotated_vec = sg_vec3_rot_xz(model->verts[i], rotate_deg);
      model->verts[i] = rotated_vec;
    }
  }

  if (rotate_ccw) {
    for (int i = 0; i < model->num_verts; i++) {
      sg_vec3 rotated_vec;
      rotated_vec = sg_vec3_rot_xz(model->verts[i], -rotate_deg);
      model->verts[i] = rotated_vec;
    }
  }

  if (rotate_fb) {
    for (int i = 0; i < model->num_verts; i++) {
      sg_vec3 rotated_vec;
      rotated_vec = sg_vec3_rot_yz(model->verts[i], -rotate_deg);
      model->verts[i] = rotated_vec;
    }
  }

  if (rotate_bf) {
    for (int i = 0; i < model->num_verts; i++) {
      sg_vec3 rotated_vec;
      rotated_vec = sg_vec3_rot_yz(model->verts[i], rotate_deg);
      model->verts[i] = rotated_vec;
    }
  }
}

void sg_window_update(unsigned int* pixels, SDL_Texture* char_tex) {
  // 3D
  SDL_RenderClear(render);
  SDL_UpdateTexture(display, NULL, pixels, VIRTUAL_WIDTH * 4); /* 320 * 4 is pitch... 4 bytes per pixel */
  SDL_RenderCopy(render, display, NULL, NULL);
  // sprite
  SDL_Rect dest;
  char test_string[] = " Weed whack, \"duck\". "; 
  sg_draw_string(test_string, 24, 128, char_tex);
  // draw
  SDL_RenderPresent(render);
}


int main() {
  sg_window_init();
  SDL_Texture* char_tex = sg_charset_init(CHARSET);

  /* TODO why does this need to be passed as a double pointer, but not later?
   *      because i want to change the value of the pointer? */

  /* TODO put renderer, screen_texture, pixels into a context that can be passed around more easily?
   */
  unsigned int* pixels = malloc(VIRTUAL_WIDTH * VIRTUAL_HEIGHT * 4);

  sg_model* model = sg_create_cube(1.0f);
   
  if (model) {
    while (1) {
      sg_model_update(model);
      sg_pixels_update(pixels, model);
      sg_window_update(pixels, char_tex);
      SDL_Delay(16); // TODO rot/scale amounts are not delta t
    }
  } else {
    printf("failed to create model.\n");
  }

  return 0;
}
