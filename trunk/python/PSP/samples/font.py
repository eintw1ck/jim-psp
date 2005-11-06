#-*- coding: ISO-8859-1 -*-

import psp2d, time

def main():
    scr = psp2d.Screen()
    img = psp2d.Image('background.png')
    font = psp2d.Font('font.png')
    img.drawText(font, 20, 20, 'Hello, world!')
    scr.blit(img)
    scr.swap()

    while True:
        pad = psp2d.Controller()
        if pad.circle:
            break

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        pass
    except:
        import traceback
        traceback.print_exc(file = file('trace.txt', 'w'))
