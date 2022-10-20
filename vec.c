/**
    @file vec.c
    @author Sean Marriott
    @author Claire Kim
    @date 20-10-2022
    @brief Provides the implementation of methods 
           used to create vector functionality.
*/

#include "vec.h"

/** Creating a instance of the Vec_t datatype 
    @param x, the vector's x-component
    @param y, the vector's y-component
    @return the new vector */
Vec_t vec(int8_t x, int8_t y) 
{
    Vec_t vector;
    vector.x = x;
    vector.y = y;
    return vector;
}

/** Adding two vectors together 
    @param vec1, the first vector
    @param vec2, the second vector
    @return the resulting vector */
Vec_t vec_add(Vec_t vec1, Vec_t vec2)
{
    Vec_t vector;
    vector.x = vec1.x + vec2.x;
    vector.y = vec1.y + vec2.y;
    return vector;
}

/** Adding only the x-component of two vectors
    @param vec1, the first vector
    @param vec2, the second vector
    @return the resulting vector */
Vec_t vec_add_x(Vec_t vec1, Vec_t vec2)
{
    Vec_t vector;
    vector.x = vec1.x + vec2.x;
    vector.y = vec1.y;
    return vector;
}

/** Adding only the y-component of two vectors
    @param vec1, the first vector
    @param vec2, the second vector
    @return the resulting vector */
Vec_t vec_add_y(Vec_t vec1, Vec_t vec2)
{
    Vec_t vector;
    vector.x = vec1.x;
    vector.y = vec1.y + vec2.y;
    return vector;
}
