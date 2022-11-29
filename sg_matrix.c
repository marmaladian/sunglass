#include "sg_matrix.h"
#include "sg_vectors.h"
#include <stdio.h>

void sg_matrix_print(sg_mat44 m) {
  printf("matrix\n");
  for (int r = 0; r < 4; r++) {
     printf("\t%.3f\t%.3f\t%.3f\t%.3f\n\n", m.m[0][r], m.m[1][r], m.m[2][r], m.m[3][r]);
  }
}

sg_mat44 sg_matrix_identity() {
/*
  sg_mat44 result;

  result.m[0][0] = 1;
  result.m[1][0] = 0;
  result.m[2][0] = 0;
  result.m[3][0] = 0;

  result.m[0][1] = 0;
  result.m[1][1] = 1;
  result.m[2][1] = 0;
  result.m[3][1] = 0;

  result.m[0][2] = 0;
  result.m[1][2] = 0;
  result.m[2][2] = 1;
  result.m[3][2] = 0;

  result.m[0][3] = 0;
  result.m[1][3] = 0;
  result.m[2][3] = 0;
  result.m[3][3] = 1;
*/
  return sg_mat44_new(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

sg_mat44 sg_mat44_new(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p) {
  sg_mat44 result;

  result.m[0][0] = a;
  result.m[1][0] = b;
  result.m[2][0] = c;
  result.m[3][0] = d;

  result.m[0][1] = e;
  result.m[1][1] = f;
  result.m[2][1] = g;
  result.m[3][1] = h;

  result.m[0][2] = i;
  result.m[1][2] = j;
  result.m[2][2] = k;
  result.m[3][2] = l;

  result.m[0][3] = m;
  result.m[1][3] = n;
  result.m[2][3] = o;
  result.m[3][3] = p;

  return result;
}

sg_mat44 sg_matrix_mul_matrix(sg_mat44 m1, sg_mat44 m2) {
  sg_mat44 result;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      /* TODO rows and columns need to be switched */
      result.m[i][j] = m1.m[i][0] * m2.m[0][j] +
                       m1.m[i][1] * m2.m[1][j] +
                       m1.m[i][2] * m2.m[2][j] +
                       m1.m[i][3] * m2.m[3][j];
    }
  }
  return result;
}

sg_mat44 sg_matrix_mul_scalar(sg_mat44 m, float s) {
  sg_mat44 result;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result.m[i][j] = m.m[i][j] * s;
    }
  }
  return result;
}


sg_vec3 sg_matrix_mul_vec3(sg_mat44 m, sg_vec3 v) {
  sg_vec3 result;
/*
  result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
  result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
  result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
  float w  = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
*/
  result.x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2] + m.m[0][3];
  result.y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2] + m.m[1][3];
  result.z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2] + m.m[2][3];
  float w  = v.x * m.m[3][0] + v.y * m.m[3][1] + v.z * m.m[3][2] + m.m[3][3];

  if (w != 1 && w != 0) {
    result.x /= w;
    result.y /= w;
    result.z /= w;
  }
  return result;
}

sg_vec3 sg_matrix_mul_dir3f(sg_mat44 m, sg_vec3 v) {
  /* mul_vec3 is for points, this is for dir/vectors
   * and does not include translation. */
  sg_vec3 result;
  /* TODO row and column need to be swapped */
  result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];
  result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];
  result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];
  return result;
}

sg_mat44 sg_matrix_transpose(sg_mat44 m) {
  sg_mat44 result;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result.m[i][j] = m.m[j][i];
    }
  }
  return result;
}

sg_mat44 sg_matrix_minors(sg_mat44 m) {
  sg_mat44 r;
  r.m[0][0] = m.m[1][1] * (m.m[2][2] * m.m[3][3] - m.m[3][2] * m.m[2][3]) - m.m[2][1] * (m.m[1][2] * m.m[3][3] - m.m[3][2] * m.m[1][3]) + m.m[3][1] * (m.m[1][2] * m.m[2][3] - m.m[2][2] * m.m[1][3]);
  r.m[1][0] = m.m[0][1] * (m.m[2][2] * m.m[3][3] - m.m[3][2] * m.m[2][3]) - m.m[2][1] * (m.m[0][2] * m.m[3][3] - m.m[3][2] * m.m[0][3]) + m.m[3][1] * (m.m[0][2] * m.m[2][3] - m.m[2][2] * m.m[0][3]);
  r.m[2][0] = m.m[0][1] * (m.m[1][2] * m.m[3][3] - m.m[3][2] * m.m[1][3]) - m.m[1][1] * (m.m[0][2] * m.m[3][3] - m.m[3][2] * m.m[0][3]) + m.m[3][1] * (m.m[0][2] * m.m[1][3] - m.m[1][2] * m.m[0][3]);
  r.m[3][0] = m.m[0][1] * (m.m[1][2] * m.m[2][3] - m.m[2][2] * m.m[1][3]) - m.m[1][1] * (m.m[0][2] * m.m[2][3] - m.m[2][2] * m.m[0][3]) + m.m[2][1] * (m.m[0][2] * m.m[1][3] - m.m[1][2] * m.m[0][3]);

  r.m[0][1] = m.m[1][0] * (m.m[2][2] * m.m[3][3] - m.m[3][2] * m.m[2][3]) - m.m[2][0] * (m.m[1][2] * m.m[3][3] - m.m[3][2] * m.m[1][3]) + m.m[3][0] * (m.m[1][2] * m.m[2][3] - m.m[2][2] * m.m[1][3]);
  r.m[1][1] = m.m[0][0] * (m.m[2][2] * m.m[3][3] - m.m[3][2] * m.m[2][3]) - m.m[2][0] * (m.m[0][2] * m.m[3][3] - m.m[3][2] * m.m[0][3]) + m.m[3][0] * (m.m[0][2] * m.m[2][3] - m.m[2][2] * m.m[0][3]);
  r.m[2][1] = m.m[0][0] * (m.m[1][2] * m.m[3][3] - m.m[3][2] * m.m[1][3]) - m.m[1][0] * (m.m[0][2] * m.m[3][3] - m.m[3][2] * m.m[0][3]) + m.m[3][0] * (m.m[0][2] * m.m[1][3] - m.m[1][2] * m.m[0][3]);
  r.m[3][1] = m.m[0][0] * (m.m[1][2] * m.m[2][3] - m.m[2][2] * m.m[1][3]) - m.m[1][0] * (m.m[0][2] * m.m[2][3] - m.m[2][2] * m.m[0][3]) + m.m[2][0] * (m.m[0][2] * m.m[1][3] - m.m[1][2] * m.m[0][3]);

  r.m[0][2] = m.m[1][0] * (m.m[2][1] * m.m[3][3] - m.m[3][1] * m.m[2][3]) - m.m[2][0] * (m.m[1][1] * m.m[3][3] - m.m[3][1] * m.m[1][3]) + m.m[3][0] * (m.m[1][1] * m.m[2][3] - m.m[2][1] * m.m[1][3]);
  r.m[1][2] = m.m[0][0] * (m.m[2][1] * m.m[3][3] - m.m[3][1] * m.m[2][3]) - m.m[2][0] * (m.m[0][1] * m.m[3][3] - m.m[3][1] * m.m[0][3]) + m.m[3][0] * (m.m[0][1] * m.m[2][3] - m.m[2][1] * m.m[0][3]);
  r.m[2][2] = m.m[0][0] * (m.m[1][1] * m.m[3][3] - m.m[3][1] * m.m[1][3]) - m.m[1][0] * (m.m[0][1] * m.m[3][3] - m.m[3][1] * m.m[0][3]) + m.m[3][0] * (m.m[0][1] * m.m[1][3] - m.m[1][1] * m.m[0][3]);
  r.m[3][2] = m.m[0][0] * (m.m[1][1] * m.m[2][3] - m.m[2][1] * m.m[1][3]) - m.m[1][0] * (m.m[0][1] * m.m[2][3] - m.m[2][1] * m.m[0][3]) + m.m[2][0] * (m.m[0][1] * m.m[1][3] - m.m[1][1] * m.m[0][3]);

  r.m[0][3] = m.m[1][0] * (m.m[2][1] * m.m[3][2] - m.m[3][1] * m.m[2][2]) - m.m[2][0] * (m.m[1][1] * m.m[3][2] - m.m[3][1] * m.m[1][2]) + m.m[3][0] * (m.m[1][1] * m.m[2][2] - m.m[2][1] * m.m[1][2]);
  r.m[1][3] = m.m[0][0] * (m.m[2][1] * m.m[3][2] - m.m[3][1] * m.m[2][2]) - m.m[2][0] * (m.m[0][1] * m.m[3][2] - m.m[3][1] * m.m[0][2]) + m.m[3][0] * (m.m[0][1] * m.m[2][2] - m.m[2][1] * m.m[0][2]);
  r.m[2][3] = m.m[0][0] * (m.m[1][1] * m.m[3][2] - m.m[3][1] * m.m[1][2]) - m.m[1][0] * (m.m[0][1] * m.m[3][2] - m.m[3][1] * m.m[0][2]) + m.m[3][0] * (m.m[0][1] * m.m[1][2] - m.m[1][1] * m.m[0][2]);
  r.m[3][3] = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[2][1] * m.m[1][2]) - m.m[1][0] * (m.m[0][1] * m.m[2][2] - m.m[2][1] * m.m[0][2]) + m.m[2][0] * (m.m[0][1] * m.m[1][2] - m.m[1][1] * m.m[0][2]);

  return r;
}

sg_mat44 sg_matrix_cofactors(sg_mat44 minors) {
  sg_mat44 r;
  r.m[0][0] =  minors.m[0][0];
  r.m[1][0] = -minors.m[1][0];
  r.m[2][0] =  minors.m[2][0];
  r.m[3][0] = -minors.m[3][0];

  r.m[0][1] = -minors.m[0][1];
  r.m[1][1] =  minors.m[1][1];
  r.m[2][1] = -minors.m[2][1];
  r.m[3][1] =  minors.m[3][1];

  r.m[0][2] =  minors.m[0][2];
  r.m[1][2] = -minors.m[1][2];
  r.m[2][2] =  minors.m[2][2];
  r.m[3][2] = -minors.m[3][2];

  r.m[0][3] = -minors.m[0][3];
  r.m[1][3] =  minors.m[1][3];
  r.m[2][3] = -minors.m[2][3];
  r.m[3][3] =  minors.m[3][3];

  return r;
}

sg_mat44 sg_matrix_adjugate(sg_mat44 cofactors) {
  sg_mat44 result;
  result = sg_matrix_transpose(cofactors);
  return result;
}

float sg_matrix_determinant(sg_mat44 m, sg_mat44 cofactors) {
  return m.m[0][0] * cofactors.m[0][0] + m.m[1][0] * cofactors.m[1][0] - m.m[2][0] * cofactors.m[2][0]  + m.m[3][0] * cofactors.m[3][0];
}

sg_mat44 sg_matrix_inverse(sg_mat44 m) {
  sg_mat44 result;
  sg_mat44 minors = sg_matrix_minors(m);
  sg_mat44 cofactors = sg_matrix_cofactors(minors);
  sg_mat44 adjugate = sg_matrix_adjugate(cofactors);
  float determinant = sg_matrix_determinant(m, cofactors);

  if (determinant == 0.0f) {
    result = sg_matrix_identity();
  } else {
    result = sg_matrix_mul_scalar(adjugate, 1/determinant);
  }

  return result;
}
