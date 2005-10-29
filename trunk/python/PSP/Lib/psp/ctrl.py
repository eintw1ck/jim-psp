#!/usr/bin/env python
#-*- coding: ISO-8859-1 -*-

#****h* /ctrl.py
#  NAME
#    ctrl -- 
#
#  CREATION DATE
#    29 Oct 2005
#***

__rcsid__ = '$Id$'

import _psp

class Controller:
    """Access to the controller."""
    def setSamplingCycle(self, sc):
        """setSamplingCycle(sc)
        Sets the controller sample rate. sc should be 0."""
        _psp.ctrlSetSamplingCycle(sc)

    def setSamplingMode(self, sm):
        """setSamplingMode(sm)
        Sets the controller sampling mode. sm must be != 0 to
        enable analog mode."""
        _psp.ctrlSetSamplingMode(sm)

    def readBufferPositive(self):
        """stamp, buttons, lx, ly = readBufferPositive()
        Returns the state of the controller. stamp is a time stamp,
        buttons an ORed value (see below), lx and ly the position
        of the analog pad. Values for buttons are

        CTRL_SELECT          Select button
        CTRL_START           Start button
        CTRL_UP              Numeric pad up
        CTRL_DOWN            Numeric pad down
        CTRL_LEFT            Numeric pad left
        CTRL_RIGHT           Numeric pad right
        CTRL_LTRIGGER        Left trigger
        CTRL_RTRIGGER        Right trigger
        CTRL_TRIANGLE        Triangle button
        CTRL_CIRCLE          Circle button
        CTRL_SQUARE          Square button
        CTRL_CROSS           Cross button
        CTRL_HOME            Home button
        CTRL_HOLD            Hold button
        CTRL_NOTE            ???"""
        return _psp.ctrlReadBufferPositive()
