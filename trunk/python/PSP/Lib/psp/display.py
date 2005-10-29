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

    def setMode(self, mode, w, h):
        """setMode(mode, w, h)
        Sets the display mode. mode is normally 0. w and h are
        the height and width."""
        _psp.displaySetMode(mode, w, h)

    def getMode(self):
        """mode, w, h = getMode()
        Returns the current display mode."""
        return _psp.displayGetMode()

    def getVcount(self):
        """c = getVcount()
        Returns the number of vertical blank pulses up to now"""
        return _psp.displayGetVcount()

    def waitVblankStart(self):
        """waitVblankStart()
        Waits for the vertical blank"""
        _psp.displayWaitVblankStart()
