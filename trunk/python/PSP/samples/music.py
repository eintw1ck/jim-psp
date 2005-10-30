#-*- coding: ISO-8859-1 -*-

__rcsid__ = '$Id$'

try:
    import psp2d
    import time

    m = psp2d.Music('stranglehold.xm')
    m.start()

    time.sleep(10)
except Exception, e:
    file('trace.txt', 'w').write('%s - %s\n' % (e.__class__.__name__, str(e)))
