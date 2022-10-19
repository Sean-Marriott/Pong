/**
    @file vec.h
    @author Sean Marriott
    @author Claire Kim
    @date 18-10-2022
    @brief Vector module header file
*/

#ifndef VEC_H
#define VEC_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/** The definition of Vec_t datatypes */
typedef struct {
    int8_t x;
    int8_t y;
} Vec_t;

/** Initilizes a instance of Vec_t*/
Vec_t vec(int8_t x, int8_t y);

/** Add two vectors*/
Vec_t vec_add(Vec_t vec1, Vec_t vec2);

/** Add only x direction of vectors*/
Vec_t vec_add_x(Vec_t vec1, Vec_t vec2);

/** Add only y direction of vectors*/
Vec_t vec_add_y(Vec_t vec1, Vec_t vec2);

#endif