#include "sg_vectors.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

sg_vec3 sg_vec3_new(float x, float y, float z) {
  sg_vec3 result;

  result.x = x;
  result.y = y;
  result.z = z;

  return result;
}

sg_vec2i sg_vec2i_new(int x, int y) {
  sg_vec2i result;

  result.x = x;
  result.y = y;

  return result;
}

sg_vec3 sg_vec3_add(sg_vec3 v1, sg_vec3 v2) {
  sg_vec3 result;

  result.x = v1.x + v2.x;
  result.y = v1.y + v2.y;
  result.z = v1.z + v2.z;

  return result;
}

sg_vec3 sg_vec3_sub(sg_vec3 v1, sg_vec3 v2) {
  sg_vec3 result;

  result.x = v1.x - v2.x;
  result.y = v1.y - v2.y;
  result.z = v1.z - v2.z;

  return result;
}

sg_vec3 sg_vec3_mult(sg_vec3 v, float m) {
  v.x *= m;
  v.y *= m;
  v.z *= m;
  return v;
}


float sg_vec3_length(sg_vec3 v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

sg_vec3 sg_vec3_normalise(sg_vec3 v) {
  float length = sg_vec3_length(v);

  if (length > 2) {
    float inv_length = 1 / sqrt(length);
    v.x *= inv_length;
    v.y *= inv_length;
    v.z *= inv_length;
  }

  return v;
}

float sg_vec3_dot(sg_vec3 v1, sg_vec3 v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

sg_vec3 sg_vec3_cross(sg_vec3 v1, sg_vec3 v2) {
  sg_vec3 result;

  result.x = v1.y * v2.z - v1.z * v2.y;
  result.y = v1.z * v2.x - v1.x * v2.z;
  result.z = v1.x * v2.y - v1.y * v2.x;

  return result;
}

const char* sg_vec3_tostring(sg_vec3 v) {
 char* str = (char*) malloc(24 * sizeof(char));
 sprintf(str, "(%.2f, %.2f, %.2f)", v.x, v.y, v.z);
 return str;
}


sg_vec3 sg_vec3_rot_xy(sg_vec3 v, float deg) {
  sg_vec3 result;
  float rad = deg * M_PI / 180;
  result.x = cos(rad) * v.x + -sin(rad) * v.y + 0 * v.z;
  result.y = sin(rad) * v.x + cos(rad) * v.y + 0 * v.z;
  result.z = 0 * v.x + 0 * v.y + 1 * v.z;
  return result;
}

sg_vec3 sg_vec3_rot_xz(sg_vec3 v, float deg) {
  sg_vec3 result;
  float rad = deg * M_PI / 180;
  result.x = cos(rad) * v.x + 0 * v.y + sin(rad) * v.z;
  result.y = 0 * v.x + 1 * v.y + 0 * v.z;
  result.z = -sin(rad) * v.x + 0 * v.y + cos(rad) * v.z;
  return result;
}

sg_vec3 sg_vec3_rot_yz(sg_vec3 v, float deg) {
  sg_vec3 result;
  float rad = deg * M_PI / 180;
  result.x = 1 * v.x + 0 * v.y + 0 * v.z;
  result.y = 0 * v.x + cos(rad) * v.y + -sin(rad) * v.z;
  result.z = 0 * v.x + sin(rad) * v.y + cos(rad) * v.z;
  return result;
}

sg_vec3 sg_vec3_scale(sg_vec3 v, sg_vec3 scale) {
  sg_vec3 result;
  result.x = scale.x * v.x + 0 * v.y + 0 * v.z;
  result.y = 0 * v.x + scale.y * v.y + 0 * v.z;
  result.z = 0 * v.x + 0 * v.y + scale.z * v.z;
  return result;
}
