#include "gumInternal.h"

void sceGumLookAt(ScePspFVector3* eye, ScePspFVector3* center, ScePspFVector3* up)
{
  ScePspFVector3 forward, side, lup,ieye;
  ScePspFMatrix4 m;

  forward.x = center->x - eye->x;
  forward.y = center->y - eye->y;
  forward.z = center->z - eye->z;

  gumNormalize(&forward);

  gumCrossProduct(&side,&forward,up);
  gumNormalize(&side);

  gumCrossProduct(&lup,&side,&forward);
  gumMakeIdentity(&m);

  m.x.x = side.x;
  m.y.x = side.y;
  m.z.x = side.z;

  m.x.y = lup.x;
  m.y.y = lup.y;
  m.z.y = lup.z;

  m.x.z = -forward.x;
  m.y.z = -forward.y;
  m.z.z = -forward.z;

  sceGumMultMatrix(&m);

  ieye.x = -eye->x; ieye.y = -eye->y; ieye.z = -eye->z;
  sceGumTranslate(&ieye);
}
