// -*- c -*-

inline void PSP2D::Screen::putPixel(u32 color, int x, int y)
{
    u32* vram = getVramDrawBuffer();
    vram[PSP_LINE_SIZE * y + x] = color;
}

inline u32 PSP2D::Screen::getPixel(int x, int y)
{
    u32* vram = getVramDrawBuffer();
    return vram[PSP_LINE_SIZE * y + x];
}
