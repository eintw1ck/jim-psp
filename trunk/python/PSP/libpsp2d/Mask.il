// -*- c -*-

inline void PSP2D::Mask::set(int x, int y)
{
    *(_data + (y) * _wcap + ((x) / 32)) |= (1U << ((x) & 31));
}

inline void PSP2D::Mask::clear(int x, int y)
{
    *(_data + (y) * _wcap + ((x) / 32)) &= ~(1U << ((x) & 31));
}

inline bool PSP2D::Mask::isSet(int x, int y)
{
    return (((*(_data + (y) * _wcap + ((x) / 32))) & (1U << ((x) & 31))) != 0);
}
