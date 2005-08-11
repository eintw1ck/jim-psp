#include "gumInternal.h"

void sceGumLoadIdentity(void)
{
  gumMakeIdentity(gum_current_matrix);
  gum_matrix_update[gum_current_mode] = 1;
}
