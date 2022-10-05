#include "vec.h"

Vec_t vec(int8_t x, int8_t y) 
{
    Vec_t vector;
    vector.x = x;
    vector.y = y;
    return vector;
}

Vec_t vec_add(Vec_t vec1, Vec_t vec2)
{
    Vec_t vecSum;
    vecSum.x = vec1.x + vec2.x;
    vecSum.y = vec1.y + vec2.y;
    return vecSum;
}

Vec_t vec_add_x(Vec_t vec1, Vec_t vec2)
{
    Vec_t vecSum;
    vecSum.x = vec1.x + vec2.x;
    vecSum.y = vec1.y;
    return vecSum;
}

Vec_t vec_add_y(Vec_t vec1, Vec_t vec2)
{
    Vec_t vecSum;
    vecSum.x = vec1.x;
    vecSum.y = vec1.y + vec2.y;
    return vecSum;
}
