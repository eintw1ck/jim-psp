#include "gumInternal.h"

#include <math.h>

void sceGumRotateX(float angle)
{
	ScePspFMatrix4 t;

	float c = cosf(angle);
	float s = sinf(angle);

	gumMakeIdentity(&t);

	t.y.y = c;
	t.y.z = s;
	t.z.y = -s;
	t.z.z = c;

	sceGumMultMatrix(&t);
}
