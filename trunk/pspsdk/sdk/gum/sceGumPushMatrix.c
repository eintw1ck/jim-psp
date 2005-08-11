#include "gumInternal.h"

#include <string.h>

void sceGumPushMatrix(void)
{
  memcpy(gum_current_matrix+1,gum_current_matrix,sizeof(ScePspFMatrix4));
  gum_current_matrix++;
}
