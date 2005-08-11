#include "gumInternal.h"

void sceGumOrtho(float left, float right, float bottom, float top, float near, float far)
{
  ScePspFMatrix4 t;
  float dx = right-left, dy = top-bottom, dz = far-near;

  gumMakeIdentity(&t);

  t.x.x = 2.0f / dx;
  t.w.x = -(right + left) / dx;
  t.y.y = 2.0f / dy;
  t.w.y = -(top + bottom) / dy;
  t.z.z = -2.0f / dz;
  t.w.z = -(far + near) / dz;

  sceGumMultMatrix(&t);
}
