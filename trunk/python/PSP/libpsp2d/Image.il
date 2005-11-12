// -*- c -*-

inline void PSP2D::Image::putPixel(u32 color, int x, int y)
{
    *(_data + y * _textureWidth + x) = color;
}

inline u32 PSP2D::Image::getPixel(int x, int y)
{
    return *(_data + y * _textureWidth + x);
}
