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
    def setSamplingCycle(self, sc):
        _psp.ctrlSetSamplingCycle(sc)

    def setSamplingMode(self, sm):
        _psp.ctrlSetSamplingMode(sm)

    def readBufferPositive(self):
        return _psp.ctrlReadBufferPositive()
