#!/usr/bin/env python
#-*- coding: ISO-8859-1 -*-

#****h* /display.py
#  NAME
#    display -- 
#
#  CREATION DATE
#    29 Oct 2005
#***

__rcsid__ = '$Id$'

import _psp

class Display:
    """Display interface"""
    def waitVblankStart(self):
        """waitVblankStart()
        Waits for the vertical scan start"""
        _psp.displayWaitVblankStart()
