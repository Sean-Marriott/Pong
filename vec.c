/**
    @file vec.c
    @author Sean Marriott
    @author Claire Kim
    @date 18-10-2022
    @brief Module containing the vector functionality.
*/

#include "vec.h"

/** Creating a instance of the Vec_t datatype */
Vec_t vec(int8_t x, int8_t y) 
{
    Vec_t vector;
    vector.x = x;
    vector.y = y;
    return vector;
}

/** Add x and y direction of vectors*/
Vec_t vec_add(Vec_t vec1, Vec_t vec2)
{
    Vec_t vecSum;
    vecSum.x = vec1.x + vec2.x;
    vecSum.y = vec1.y + vec2.y;
    return vecSum;
}

/** Add only x direction of vector*/
Vec_t vec_add_x(Vec_t vec1, Vec_t vec2)
{
    Vec_t vecSum;
    vecSum.x = vec1.x + vec2.x;
    vecSum.y = vec1.y;
    return vecSum;
}

/** Add only y direction of vector*/
Vec_t vec_add_y(Vec_t vec1, Vec_t vec2)
{
    Vec_t vecSum;
    vecSum.x = vec1.x;
    vecSum.y = vec1.y + vec2.y;
    return vecSum;
}
