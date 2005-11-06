#-*- coding: ISO-8859-1 -*-

import psp2d, time

def main():
    scr = psp2d.Screen()
    img = psp2d.Image('background.png')
    font = psp2d.Font('font.png')
    img.drawText(font, 20, 20, 'Hello, world!')
    scr.blit(0, 0, img.width, img.height, img, 0, 0)
    scr.swap()

    time.sleep(10)

if __name__ == '__main__':
    try:
        main()
    except:
        import traceback
        traceback.print_exc(file = file('trace.txt', 'w'))
