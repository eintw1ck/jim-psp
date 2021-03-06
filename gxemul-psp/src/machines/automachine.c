/*
 *  DO NOT EDIT. AUTOMATICALLY CREATED
 */

/*
 *  Copyright (C) 2005-2006  Anders Gavare.  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright  
 *     notice, this list of conditions and the following disclaimer in the 
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE   
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *   
 *
 *  $Id: automachine_head.c,v 1.3 2005/12/31 15:47:38 debug Exp $
 *
 *  Automatically register all machines in the src/machines/ subdir.
 *
 *  NOTE: automachine_head.c, plus a line for each machine, plus
 *  automachine_middle.c, plus another line (again) for each machine, plus
 *  automachine_tail.c should be combined into one. See makeautomachine.sh
 *  for more info.
 */

#include <stdio.h>

#include "machine.h"

void machine_register_psp(void);

/*  $Id: automachine_middle.c,v 1.1 2005/12/20 21:19:17 debug Exp $  */

/*
 *  automachine_init():
 */
void automachine_init(void)
{
	/*  printf("automachine_init()\n");  */

	/*  automachine_middle.c ends here.  */

	machine_register_psp();

	/*  $Id: automachine_tail.c,v 1.1 2005/12/20 21:19:17 debug Exp $  */
}

