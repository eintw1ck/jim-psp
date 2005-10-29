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
    """Interface with the kernel."""
    def DcacheWritebackAll(self):
        """DcacheWritebackAll()
        Write the data cache to memory"""
        _psp.kernelDcacheWritebackAll()
