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
    """Access to the debug screen."""
    def __init__(self):
        """DebugScreen()
        Initializes the debug screen."""
        _psp.debugScreenInit()

    def printf(self, fmt, *args):
        """printf(fmt, *args)
        Formats a message and sends it to the debug screen.
        Ending LF is not included."""
        _psp.debugScreenPrint(fmt % args)

    def setBackColor(self, r, g, b, a = 0):
        """setBackColor(r, g, b, a = 0)
        Sets the background color."""
        _psp.debugScreenSetBackColor(r, g, b, a)

    def setTextColor(self, r, g, b, a = 0):
        """setTextColor(r, g, b, a = 0)
        Sets the text color."""
        _psp.debugScreenSetTextColor(r, g, b, a)

    def putChar(self, x, y, char, r, g, b, a = 0):
        """putChar(x, y, char, r, g, b, a = 0)
        Puts the specified character at the specified position,
        using the (r, g, b, a) color."""
        _psp.debugScreenPutChar(x, y, char, r, g, b, a)

    def setXY(self, x, y):
        """setXY(x, y)
        Sets the cursor position."""
        _psp.debugScreenSetXY(x, y)

    def getX(self):
        """x = getX()
        Returns the cursor position in X."""
        return _psp.debugScreenGetX()

    def getY(self):
        """y = getY()
        Returns the cursor position in Y."""
        return _psp.debugScreenGetY()

    def getXY(self):
        """x, y = getXY()
        Returns the cursor position as a 2-tuple (x, y)"""
        return (self.getX(), self.getY())

    def clear(self):
        """clear()
        Clears the debug screen."""
        _psp.debugScreenClear()
