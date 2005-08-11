#include "gumInternal.h"

void sceGumPopMatrix(void)
{
  gum_current_matrix--;
  gum_matrix_update[gum_current_mode] = 1;
}
