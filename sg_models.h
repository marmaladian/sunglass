#ifndef SG_MODELS
#define SG_MODELS
#include "sg_vectors.h"
#include <stdlib.h>

typedef struct sg_model {
  sg_vec3* verts;
  int num_verts;
  int* tris;
  int num_tris;
} sg_model;

void sg_destroy_model(sg_model* m);
sg_model* sg_create_plane(int width, int length);
sg_model* sg_create_terrain(int width, int length, float max_height);
sg_model* sg_create_cube(float scale);
sg_model* sg_create_xmastree();

#endif
