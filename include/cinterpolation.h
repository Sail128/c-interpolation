/**
 * @file interpolate.h
 * @author Sail128 ()
 * @brief
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _C_INTERPOLATION_H_
#define _C_INTERPOLATION_H_

// enum{}interpolation_method;



typedef enum 
{
    CLOSEST_POINT,
    ZERO_OUTSIDE
}edge_behaviour_t;

typedef enum {STEP_LEFT_INTERP, STEP_RIGHT_INTERP, STEP_CENTER_INTERP, LINEAR_INTERP}interpolation_method_t;

typedef struct
{
    interpolation_method_t method;
    edge_behaviour_t edge;
    int n;    // number of points in the list
    float *x; // ordered point list
    float *y; // ordered point list
} interpolate_t;

float interpolate_step_left(interpolate_t *interp, float x);
float interpolate_step_right(interpolate_t *interp, float x);
float interpolate_step_center(interpolate_t *interp, float x);
float interpolate_linear(interpolate_t *interp, float x);


float get_interpolated_point(interpolate_t *, float x);

#endif // _C_INTERPOLATION_H_
