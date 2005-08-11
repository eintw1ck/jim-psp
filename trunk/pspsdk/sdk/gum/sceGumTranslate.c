#include "gumInternal.h"

void sceGumTranslate(const ScePspFVector3* v)
{
	ScePspFMatrix4 t;

	gumMakeIdentity(&t);
	t.w.x = v->x;
	t.w.y = v->y;
	t.w.z = v->z;

	sceGumMultMatrix(&t);
/*
  ScePspFVector4 t;
  ScePspFMatrix4* curr = gum_current_matrix;
  float x,y,z;

  x = v->x; y = v->y; z = v->z;

  t.x = v->x * curr->x.x + y * curr->y.x + z * curr->z.x + curr->w.x;
  t.y = v->x * curr->x.y + y * curr->y.y + z * curr->z.y + curr->w.y;
  t.z = v->x * curr->x.z + y * curr->y.z + z * curr->z.z + curr->w.z;
  t.w = v->x * curr->x.w + y * curr->y.w + z * curr->z.w + curr->w.w;

  curr->w = t;

  gum_matrix_update[gum_current_mode] = 1;
*/
}
