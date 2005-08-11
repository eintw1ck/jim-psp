#include "gumInternal.h"

void sceGumMatrixMode(int mode)
{
  gum_stack_depth[gum_current_mode] = gum_current_matrix;

  gum_current_matrix = gum_stack_depth[mode];
  gum_current_mode = mode;
}
