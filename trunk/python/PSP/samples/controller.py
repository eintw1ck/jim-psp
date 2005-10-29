#-*- coding: ISO-8859-1 -*-

try:
    import psp

    scr = psp.debug.DebugScreen()
    ctl = psp.ctrl.Controller()

    ctl.setSamplingCycle(0)
    ctl.setSamplingMode(1)

    while True:
        scr.clear()
        scr.setXY(0, 2)
        stamp, buttons, analog_x, analog_y = ctl.readBufferPositive()

        scr.printf('Analog X: %d Analog Y: %d\n', analog_x, analog_y)

        for button in ('SQUARE', 'TRIANGLE', 'CROSS', 'CIRCLE', 'UP', 'DOWN',
                       'LEFT', 'RIGHT', 'START', 'SELECT', 'LTRIGGER',
                       'RTRIGGER'):
            mask = getattr(psp, 'CTRL_' + button)
            if buttons & mask != 0:
                scr.printf('%s button pressed.\n', button)
except Exception, e:
    file('trace.txt', 'w').write('%s - %s\n' % (e.__class__.__name__, str(e)))
