#-*- coding: ISO-8859-1 -*-

__rcsid__ = '$Id$'

try:
    import psp2d, time

    scr = psp2d.Screen()

    img = psp2d.Image('test.png')
    scr.blit(0, 0, img.width, img.height, img, 0, 0)

    img = psp2d.Image(200, 200)
    img.clear(psp2d.Color(255, 0, 0))
    scr.blit(0, 0, 200, 200, img, 30, 30)

    scr.swap()

    time.sleep(10)
except Exception, e:
    file('trace.txt', 'w').write('%s - %s\n' % (e.__class__.__name__, str(e)))
