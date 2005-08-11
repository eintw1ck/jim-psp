/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

#include <math.h>

void sceGumPerspective(float fovy, float aspect, float near, float far)
{
  ScePspFMatrix4 t;

  float angle = (fovy / 2) * (M_PI/180.0f);
  float cotangent = cosf(angle) / sinf(angle);
  float delta_z = near-far;

  gumMakeIdentity(&t);

  t.x.x = cotangent / aspect;
  t.y.y = cotangent;
  t.z.z = (far + near) / delta_z; // -(far + near) / delta_z
  t.w.z = 2 * (far * near) / delta_z; // -2 * (far * near) / delta_z
  t.z.w = -1;
  t.w.w = 0;

  sceGumMultMatrix(&t);
}
