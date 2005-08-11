#include "gumInternal.h"

void sceGumMultMatrix(const ScePspFMatrix4* m)
{
  gumMultMatrix(gum_current_matrix,gum_current_matrix,m);  
}
