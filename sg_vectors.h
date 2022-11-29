#ifndef SG_VECTORS_INCLUDED
#define SG_VECTORS_INCLUDED

typedef struct sg_vec3 {
  float x, y, z;
} sg_vec3;

typedef struct sg_vec2i {
  int x, y;
} sg_vec2i;

typedef struct sg_vec2f {
  float x, y;
} sg_vec2f;

sg_vec3 sg_vec3_new(float x, float y, float z);
sg_vec2i sg_vec2i_new(int x, int y);
sg_vec3 sg_vec3_add(sg_vec3 v1, sg_vec3 v2);
sg_vec3 sg_vec3_sub(sg_vec3 v1, sg_vec3 v2);
sg_vec3 sg_vec3_mult(sg_vec3 v, float m);

float sg_vec3_length(sg_vec3 v);
float sg_vec3_dot(sg_vec3 v1, sg_vec3 v2);

sg_vec3 sg_vec3_normalise(sg_vec3 v);
sg_vec3 sg_vec3_cross(sg_vec3 v1, sg_vec3 v2);

const char* sg_vec3_tostring(sg_vec3 v);

sg_vec3 sg_vec3_rot_xy(sg_vec3 v, float deg);
sg_vec3 sg_vec3_rot_xz(sg_vec3 v, float deg);
sg_vec3 sg_vec3_rot_yz(sg_vec3 v, float deg);

sg_vec3 sg_vec3_scale(sg_vec3 v, sg_vec3 scale);

#endif
