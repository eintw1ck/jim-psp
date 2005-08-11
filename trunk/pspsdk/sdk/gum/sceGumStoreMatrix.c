#include "gumInternal.h"

#include <string.h>

void sceGumStoreMatrix(ScePspFMatrix4* m)
{
  memcpy(m,gum_current_matrix,sizeof(ScePspFMatrix4));
}
