#include "gumInternal.h"

void sceGumRotateXYZ(const ScePspFVector3* v)
{
	sceGumRotateZ(v->z);
	sceGumRotateY(v->y);
	sceGumRotateX(v->x);
}
