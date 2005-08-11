#include "gumInternal.h"
#include <string.h>

void sceGumLoadMatrix(const ScePspFMatrix4* m)
{
  memcpy(gum_current_matrix,m,sizeof(ScePspFMatrix4));
  gum_matrix_update[gum_current_mode] = 1;
}
