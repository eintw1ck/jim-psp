#!/usr/bin/env python
#-*- coding: ISO-8859-1 -*-

#****h* /kernel.py
#  NAME
#    kernel -- 
#
#  CREATION DATE
#    29 Oct 2005
#***

__rcsid__ = '$Id$'

import _psp

class Kernel:
    def DcacheWritebackAll(self):
        _psp.kernelDcacheWritebackAll()
