#ifndef VEC_H
#define VEC_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int8_t x;
    int8_t y;
} Vec_t;

Vec_t vec(int8_t x, int8_t y);

Vec_t vec_add(Vec_t vec1, Vec_t vec2);

Vec_t vec_add_x(Vec_t vec1, Vec_t vec2);

Vec_t vec_add_y(Vec_t vec1, Vec_t vec2);

#endif