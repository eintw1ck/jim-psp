/*                          ____  _     
#         ____  _________  / __ \(_)____
#        / __ \/ ___/ __ \/ / / / / ___/
#       / /_/ (__  ) /_/ / /_/ / (__  ) 
#      / .___/____/ .___/_____/_/____/  
#     /_/        /_/
#     
# Copyright 2005, pspdev - http://www.pspdev.org
# Author:       John Kelley
# Date:         June 1 2005
# File:         pspdis.h
# Description:  Disassembler for PSP Allegrex binaries.
#
*/
#ifndef _PSPDIS_H_
#define _PSPDIS_H_

#include <vector>
#include <map>
#include "util.h"

#define PSPDISVER "0.2pre"
#define dprintf(a...)	if(VERBOSE > 0) printf(a);
#define VERBOSE 1

typedef std::map<u32, std::vector<u32> > xref_type;

#endif
