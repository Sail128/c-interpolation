/**
 * @file interpolate.c
 * @author Sail128 ()
 * @brief
 * @version 0.1
 * @date 2022-01-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "cinterpolation.h"

/**
 * @brief returns value for give edge behaviour
 *
 * @param behavior
 * @param ege 0 lower, 1 upper
 * @return float
 */
float interpolate_edge(interpolate_t *interp, int edge)
{
    if (edge)
    {
        switch (interp->edge)
        {
        case CLOSEST_POINT:
            return interp->y[interp->n - 1];
            break;
        case ZERO_OUTSIDE:
            return 0;
            break;
        }
    }
    else
    {
        switch (interp->edge)
        {
        case CLOSEST_POINT:
            return interp->y[0];
            break;
        case ZERO_OUTSIDE:
            return 0;
            break;
        }
    }
}

/**
 * @brief step interpolation left value gives step
 *
 * @param x
 * @return float
 */
float interpolate_step_left(interpolate_t *interp, float x)
{
    // assigning stuct values to pointers to not have to type everything out everytime.
    float *xs = interp->x;
    float *ys = interp->y;

    if (x <= xs[0])
    {
        // lower bound check
        return interpolate_edge(interp, 0);
    }
    else if (x > xs[interp->n - 1])
    {
        // upper bound check
        return interpolate_edge(interp, 1);
    }

    for (int i = 1; i < interp->n; i++)
    {
        if (x < xs[i])
        {
            return ys[i - 1];
        }
    }
}

/**
 * @brief step interpolation right value gives step
 *
 * @param interp
 * @param x
 * @return float
 */
float interpolate_step_right(interpolate_t *interp, float x)
{
    // assigning stuct values to pointers to not have to type everything out everytime.
    float *xs = interp->x;
    float *ys = interp->y;

    if (x <= xs[0])
    {
        // lower bound check
        return interpolate_edge(interp, 0);
    }
    else if (x > xs[interp->n - 1])
    {
        // upper bound check
        return interpolate_edge(interp, 1);
    }

    for (int i = 1; i < interp->n; i++)
    {
        if (x < xs[i])
        {
            return ys[i];
        }
    }
}

/**
 * @brief step interpolation step value switches at center between points
 *
 * @param interp
 * @param x
 * @return float
 */
float interpolate_step_center(interpolate_t *interp, float x)
{
    // assigning stuct values to pointers to not have to type everything out everytime.
    float *xs = interp->x;
    float *ys = interp->y;

    if (x <= xs[0])
    {
        // lower bound check
        return interpolate_edge(interp, 0);
    }
    else if (x > xs[interp->n - 1])
    {
        // upper bound check
        return interpolate_edge(interp, 1);
    }

    for (int i = 1; i < interp->n; i++)
    {
        if (x < xs[i])
        {
            // return ys[i-1];
            float mid = xs[i] - xs[i - 1];
            if (x > mid)
                return xs[i];
            else
                return xs[i - 1];
        }
    }
}

/**
 * @brief linear interpolation between points
 *
 * @param interp pointer to interpolate_t struct containing relevant stuff
 * @param x coordinate to get interpolated value for.
 * @return float
 */
float interpolate_linear(interpolate_t *interp, float x)
{
    float *xs = interp->x;
    float *ys = interp->y;

    if (x <= xs[0])
    {
        // lower bound check
        return interpolate_edge(interp, 0);
    }
    else if (x > xs[interp->n - 1])
    {
        // upper bound check
        return interpolate_edge(interp, 1);
    }

    for (int i = 1; i < interp->n; i++)
    {
        if (x < xs[i])
        {
            return ((ys[i] - ys[i - 1]) * (x - xs[i - 1])) / (xs[i] - xs[i - 1]) + ys[i - 1];
        }
    }
}
