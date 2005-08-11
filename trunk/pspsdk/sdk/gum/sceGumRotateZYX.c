#include "gumInternal.h"

void sceGumRotateXYZ(const ScePspFVector3* v)
{
	sceGumRotateX(v->z);
	sceGumRotateY(v->y);
	sceGumRotateZ(v->x);
}
