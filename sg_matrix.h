#ifndef SG_MATRIX_INCLUDED
#define SG_MATRIX_INCLUDED

#include "sg_vectors.h"

typedef struct sg_mat44 {
  float m[4][4]; /* [col][row] */
} sg_mat44;

sg_mat44 sg_matrix_mul_matrix(sg_mat44 m1, sg_mat44 m2);
sg_mat44 sg_matrix_mul_scalar(sg_mat44 m, float s); 
sg_vec3 sg_matrix_mul_vec3(sg_mat44 m, sg_vec3 v);
sg_vec3 sg_matrix_mul_dir3f(sg_mat44 m, sg_vec3 v);
sg_mat44 sg_matrix_transpose(sg_mat44 m);
sg_mat44 sg_mat44_new(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);

sg_mat44 sg_matrix_identity();

sg_mat44 sg_matrix_minors(sg_mat44 m);
sg_mat44 sg_matrix_cofactors(sg_mat44 minors); 
sg_mat44 sg_matrix_adjugate(sg_mat44 cofactors);
float sg_matrix_determinant(sg_mat44 m, sg_mat44 cofactors);
sg_mat44 sg_matrix_inverse(sg_mat44 m);
void sg_matrix_print(sg_mat44 m);


#endif
