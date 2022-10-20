/**
    @file vec.h
    @author Sean Marriott
    @author Claire Kim
    @date 20-10-2022
    @brief Vector module header file. Provides the methods
           for the vector functionality.
*/

#ifndef VEC_H
#define VEC_H

#include "system.h"

/** The definition of Vec_t datatypes */
typedef struct {
    int8_t x;
    int8_t y;
} Vec_t;

/** Creating a instance of the Vec_t datatype 
    @param x, the vector's x-component
    @param y, the vector's y-component
    @return the new vector */
Vec_t vec(int8_t x, int8_t y);

/** Adding two vectors together 
    @param vec1, the first vector
    @param vec2, the second vector
    @return the resulting vector */
Vec_t vec_add(Vec_t vec1, Vec_t vec2);

/** Adding only the x-component of two vectors
    @param vec1, the first vector
    @param vec2, the second vector
    @return the resulting vector */
Vec_t vec_add_x(Vec_t vec1, Vec_t vec2);

/** Adding only the y-component of two vectors
    @param vec1, the first vector
    @param vec2, the second vector
    @return the resulting vector */
Vec_t vec_add_y(Vec_t vec1, Vec_t vec2);

#endif