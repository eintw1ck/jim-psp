#-*- coding: ISO-8859-1 -*-

import psp

psp.debugScreenInit()

try:
    psp.ctrlSetSamplingCycle(0)
    psp.ctrlSetSamplingMode(1)

    while True:
        psp.debugScreenSetXY(0, 2)
        stamp, buttons, analog_x, analog_y = psp.ctrlReadBufferPositive()

        psp.debug('Analog X: %d Analog Y: %d\n' % (analog_x, analog_y))

        for button in ('SQUARE', 'TRIANGLE', 'CROSS', 'CIRCLE', 'UP', 'DOWN',
                       'LEFT', 'RIGHT', 'START', 'SELECT', 'LTRIGGER',
                       'RTRIGGER'):
            mask = getattr(psp, 'CTRL_' + button)
            if buttons & mask != 0:
                psp.debug('%s button pressed.\n' % button)
except Exception, e:
    import time

    psp.debug('Exception: %s - %s' % (e.__class__.__name__, str(e)))
    time.sleep(5)
