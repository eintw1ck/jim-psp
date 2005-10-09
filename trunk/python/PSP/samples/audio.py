#-*- coding: ISO-8859-1 -*-

# DOES NOT WORK YET

try:
    import psp
    import math, struct

    tm = 0.000000

    def audioCallback(sz):
        bf = []
        for i in xrange(sz):
            s = int(0xFFFF * math.sin(2.0 * math.pi * 440 * tm))
            bf.append(struct.pack('>HH', s, s))
            tm += 1.0 / 44100
        return ''.join(bf)

    psp.debugScreenInit()
    psp.debug('Playing...')

    psp.audioInit()
    psp.audioSetChannelCallback(0, audioCallback)

    while True:
        pass

except Exception, e:
    psp.debug('Exception: %s - %s' % (e.__class__.__name__, str(e)))
