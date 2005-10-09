
#ifndef _MATRIX_H_
#define _MATRIX_H_

void matrix_identity(float*);
void matrix_projection(float*, float, float, float, float);
void matrix_multiply(float*, float*, float*);
void matrix_translate(float*, float, float, float);
void matrix_setrotatex(float*, float);
void matrix_setrotatey(float*, float);
void matrix_setrotatez(float*, float);
void matrix_rotate(float*, float, float, float);

#endif /* _MATRIX_H_ */
