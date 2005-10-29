#!/usr/bin/env python
#-*- coding: ISO-8859-1 -*-

#****h* /dbgcolor.py
#  NAME
#    dbgcolor -- 
#
#  CREATION DATE
#    29 Oct 2005
#***

__rcsid__ = '$Id$'

import time, psp

def main():
    scr = psp.debug.DebugScreen()

    scr.setBackColor(0, 0, 0xFF)
    scr.setTextColor(0xFF, 0, 0)
    scr.printf("Should be red on blue.")

    time.sleep(10)

if __name__ == '__main__':
    try:
        main()
    except Exception, e:
        file('trace.txt', 'w').write('%s - %s\n' % (e.__class__.__name__, str(e)))
