#include "gumInternal.h"

void sceGumDrawArray(int prim, int vtype, int count, const void* indices, const void* vertices)
{
  sceGumUpdateMatrix();
  sceGuDrawArray(prim,vtype,count,indices,vertices);
}
