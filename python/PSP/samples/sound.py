#-*- coding: ISO-8859-1 -*-

__rcsid__ = '$Id$'

try:
    import time, os, psp2d

    name = 'explode.wav'

    if not os.path.exists(name):
        raise IOError('File does not exist')

    s = psp2d.Sound(name)

    time.sleep(5)
    s.start()
    time.sleep(5)
except Exception, e:
    file('trace.txt', 'w').write('%s - %s\n' % (e.__class__.__name__, str(e)))
