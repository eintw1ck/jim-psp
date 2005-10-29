#!/usr/bin/env python
#-*- coding: ISO-8859-1 -*-

#****h* /debug.py
#  NAME
#    debug -- Wrapper for pspdebug
#
#  CREATION DATE
#    29 Oct 2005
#***

"""

Wrapper for pspdebug

"""

__rcsid__ = '$Id$'

import _psp

class DebugScreen:
    def __init__(self):
        _psp.debugScreenInit()

    def printf(self, fmt, *args):
        _psp.debugScreenPrint(fmt % args)

    def setBackColor(r, g, b, a = 0):
        _psp.debugScreenSetBackColor(r, g, b, a)

    def setTextColor(r, g, b, a = 0):
        _psp.debugScreenSetTextColor(r, g, b, a)

    def putChar(x, y, char, r, g, b, a = 0):
        _psp.debugScreenPutChar(x, y, char, r, g, b, a)

    def setXY(self, x, y):
        _psp.debugScreenSetXY(x, y)

    def getX(self):
        return _psp.debugScreenGetX()

    def getY(self):
        return _psp.debugScreenGetY()

    def clear(self):
        _psp.debugScreenClear()
