#include "gumInternal.h"

void sceGumScale(const ScePspFVector3* v)
{
  ScePspFMatrix4* curr = gum_current_matrix;
  float x,y,z;

  x = v->x; y = v->y; z = v->z;
  curr->x.x *= x; curr->x.y *= x; curr->x.z *= x;
  curr->y.x *= x; curr->y.y *= x; curr->y.z *= x;
  curr->z.x *= x; curr->z.y *= x; curr->z.z *= x;

  gum_matrix_update[gum_current_mode] = 1;
}
