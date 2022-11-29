#include "sg_models.h"
#include <stdio.h>
#include <string.h>

sg_model* sg_create_plane(int width, int length) {
  sg_model* m = malloc(sizeof(*m));
  if (!m) {
    printf("failed to allocate memory for model.\n");
    return NULL;
  }

  printf("sizeof(m->verts): %lu\n", width * length * sizeof(m->verts));
  m->verts = malloc(width * length * sizeof(sg_vec3));
  if (!m->verts) {
    free(m);
    printf("failed to allocate memory for vertices.\n");
    return NULL;
  }

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      m->verts[j + i * width] = sg_vec3_new(i * 0.01f, 0.1, j * 0.01f);
    }
  }
  m->num_verts = width * length;
  printf("%i verts.\n", m->num_verts);
  return m;
}

sg_model* sg_create_terrain(int width, int length, float max_height) {
  sg_model* m = malloc(sizeof(*m));
  if(!m) {
    printf("failed to allocate memory for model.\n");
    return NULL;
  }
  
  printf("sizeof(m->verts): %lu\n", width * length * sizeof(m->verts));
  m->verts = malloc(width * length * sizeof(sg_vec3));
  if (!m->verts) {
    free(m);
    printf("failed to allocate memory for vertices.\n");
    return NULL;
  }

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      float height = (float) rand() / (float) (RAND_MAX / max_height);
      m->verts[j + i * width] = sg_vec3_new(i * 0.01f, height, j * 0.01f);
    }
  }
  m->num_verts = width * length;
  printf("%i verts.\n", m->num_verts);
  return m;
}

void sg_destroy_model(sg_model* m) {
  free(m->verts);
  free(m);
}

sg_model* sg_create_cube(float scale) {
  sg_model* m = malloc(sizeof(*m));
  if (!m) {
    printf("failed to allocate memory for model.\n");
    return NULL;
  }

  m->verts = malloc(8 * sizeof(sg_vec3));
  if (!m->verts) {
    free(m);
    printf("failed to allocate memory for vertices.\n");
    return NULL;
  }

  m->verts[0] = sg_vec3_new(0, 0, 0); 
  m->verts[1] = sg_vec3_new(0, 0, scale); 
  m->verts[2] = sg_vec3_new(scale, 0, 0); 
  m->verts[3] = sg_vec3_new(scale, 0, scale); 
  m->verts[4] = sg_vec3_new(0, scale, 0); 
  m->verts[5] = sg_vec3_new(0, scale, scale); 
  m->verts[6] = sg_vec3_new(scale, scale, 0); 
  m->verts[7] = sg_vec3_new(scale, scale, scale); 

  m->num_verts = 8;

  m->tris = malloc(12 * 3 * sizeof(int)); 

  int tmp_tris[] = { 1, 0, 2,
                     1, 3, 2,

                     0, 6, 4,
                     0, 2, 6,

                     4, 7, 5,
                     4, 6, 7,

                     5, 3, 1,
                     5, 7, 3,

                     2, 7, 6,
                     2, 3, 7,

                     1, 4, 5,
                     1, 0, 4
  };
  
  memcpy(m->tris, tmp_tris, sizeof tmp_tris);

  m->num_tris = 36;

  return m;
}

sg_model* sg_create_xmastree() {
  sg_model* m = malloc(sizeof(*m));
  if(!m) {
    printf("failed to allocate memory for model.\n");
    return NULL;
  }
  
  m->verts = malloc(146 * sizeof(sg_vec3));
  if (!m->verts) {
    free(m);
    printf("failed to allocate memory for vertices.\n");
    return NULL;
  }

  sg_vec3 x[] = {
    {        0,    39.034,         0}, {  0.76212,    36.843,         0},
    {        3,    36.604,         0}, {        1,    35.604,         0},
    {   2.0162,    33.382,         0}, {        0,    34.541,         0},
    {  -2.0162,    33.382,         0}, {       -1,    35.604,         0},
    {       -3,    36.604,         0}, { -0.76212,    36.843,         0},
    {-0.040181,     34.31,         0}, {   3.2778,    30.464,         0},
    {-0.040181,    30.464,         0}, {-0.028749,    30.464,         0},
    {   3.2778,    30.464,         0}, {   1.2722,    29.197,         0},
    {   1.2722,    29.197,         0}, {-0.028703,    29.197,         0},
    {   1.2722,    29.197,         0}, {   5.2778,    25.398,         0},
    { -0.02865,    25.398,         0}, {   1.2722,    29.197,         0},
    {   5.2778,    25.398,         0}, {   3.3322,    24.099,         0},
    {-0.028683,    24.099,         0}, {   7.1957,    20.299,         0},
    { -0.02861,    20.299,         0}, {   5.2778,    19.065,         0},
    {-0.028663,    18.984,         0}, {   9.2778,    15.265,         0},
    {-0.028571,    15.185,         0}, {   9.2778,    15.265,         0},
    {   7.3772,    13.999,         0}, {-0.028625,    13.901,         0},
    {   9.2778,    15.265,         0}, {   12.278,    8.9323,         0},
    {-0.028771,    8.9742,         0}, {   12.278,    8.9323,         0},
    {   10.278,    7.6657,         0}, {-0.028592,    7.6552,         0},
    {   15.278,    2.5994,         0}, {-0.028775,    2.6077,         0},
    {   15.278,    2.5994,         0}, {   13.278,    1.3329,         0},
    {-0.028727,    1.2617,         0}, {   18.278,   -3.7334,         0},
    {   18.278,   -3.7334,         0}, {   2.2722,   -1.2003,         0},
    {-0.028727,   -1.3098,         0}, {   4.2722,        -5,         0},
    {   4.2722,        -5,         0}, {-0.028727,        -5,         0},
    {  -3.3582,    30.464,         0}, {  -3.3582,    30.464,         0},
    {  -1.3526,    29.197,         0}, {  -1.3526,    29.197,         0},
    {  -1.3526,    29.197,         0}, {  -5.3582,    25.398,         0},
    {  -1.3526,    29.197,         0}, {  -5.3582,    25.398,         0},
    {  -3.4126,    24.099,         0}, {   -7.276,    20.299,         0},
    {  -5.3582,    19.065,         0}, {  -9.3582,    15.265,         0},
    {  -9.3582,    15.265,         0}, {  -7.4575,    13.999,         0},
    {  -9.3582,    15.265,         0}, {  -12.358,    8.9323,         0},
    {  -12.358,    8.9323,         0}, {  -10.358,    7.6657,         0},
    {  -15.358,    2.5994,         0}, {  -15.358,    2.5994,         0},
    {  -13.358,    1.3329,         0}, {  -18.358,   -3.7334,         0},
    {  -18.358,   -3.7334,         0}, {  -2.3526,   -1.2003,         0},
    {  -4.3526,        -5,         0}, {  -4.3526,        -5,         0},
    {        0,     34.31,  0.040181}, {        0,    30.464,   -3.2778},
    {        0,    30.464,  0.040181}, {        0,    30.464,  0.028749},
    {        0,    30.464,   -3.2778}, {        0,    29.197,   -1.2722},
    {        0,    29.197,   -1.2722}, {        0,    29.197,  0.028703},
    {        0,    29.197,   -1.2722}, {        0,    25.398,   -5.2778},
    {        0,    25.398,   0.02865}, {        0,    29.197,   -1.2722},
    {        0,    25.398,   -5.2778}, {        0,    24.099,   -3.3322},
    {        0,    24.099,  0.028683}, {        0,    20.299,   -7.1957},
    {        0,    20.299,   0.02861}, {        0,    19.065,   -5.2778},
    {        0,    18.984,  0.028663}, {        0,    15.265,   -9.2778},
    {        0,    15.185,  0.028571}, {        0,    15.265,   -9.2778},
    {        0,    13.999,   -7.3772}, {        0,    13.901,  0.028625},
    {        0,    15.265,   -9.2778}, {        0,    8.9323,   -12.278},
    {        0,    8.9742,  0.028771}, {        0,    8.9323,   -12.278},
    {        0,    7.6657,   -10.278}, {        0,    7.6552,  0.028592},
    {        0,    2.5994,   -15.278}, {        0,    2.6077,  0.028775},
    {        0,    2.5994,   -15.278}, {        0,    1.3329,   -13.278},
    {        0,    1.2617,  0.028727}, {        0,   -3.7334,   -18.278},
    {        0,   -3.7334,   -18.278}, {        0,   -1.2003,   -2.2722},
    {        0,   -1.3098,  0.028727}, {        0,        -5,   -4.2722},
    {        0,        -5,   -4.2722}, {        0,        -5,  0.028727},
    {        0,    30.464,    3.3582}, {        0,    30.464,    3.3582},
    {        0,    29.197,    1.3526}, {        0,    29.197,    1.3526},
    {        0,    29.197,    1.3526}, {        0,    25.398,    5.3582},
    {        0,    29.197,    1.3526}, {        0,    25.398,    5.3582},
    {        0,    24.099,    3.4126}, {        0,    20.299,     7.276},
    {        0,    19.065,    5.3582}, {        0,    15.265,    9.3582},
    {        0,    15.265,    9.3582}, {        0,    13.999,    7.4575},
    {        0,    15.265,    9.3582}, {        0,    8.9323,    12.358},
    {        0,    8.9323,    12.358}, {        0,    7.6657,    10.358},
    {        0,    2.5994,    15.358}, {        0,    2.5994,    15.358},
    {        0,    1.3329,    13.358}, {        0,   -3.7334,    18.358},
    {        0,   -3.7334,    18.358}, {        0,   -1.2003,    2.3526},
    {        0,        -5,    4.3526}, {        0,        -5,    4.3526}
  };

  for (int i = 0; i < 146; i++) {
    m->verts[i] = x[i];
  }
  printf("%s", sg_vec3_tostring(m->verts[3]));
  m->num_verts = 146;
  return m;
}
