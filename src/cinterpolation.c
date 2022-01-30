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

    return 0.0; // shouldn't reach here but theorethically not impossible.
}

float catmullSlope(float x[], float y[], int n, int i)
{
    if (x[i + 1] == x[i - 1])
        return 0;
    return (y[i + 1] - y[i - 1]) / (x[i + 1] - x[i - 1]);
}

float interpolate_catmulspline(interpolate_t *interp, float x)
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

    int i = 0;
    while (x >= xs[i + 1])
        i++;
    if (x == xs[i + 1])
        return ys[i + 1];
    float t = (x - xs[i]) / (xs[i + 1] - xs[i]);
    float t_2 = t * t;
    float t_3 = t_2 * t;

    float h00 = 2 * t_3 - 3 * t_2 + 1;
    float h10 = t_3 - 2 * t_2 + t;
    float h01 = 3 * t_2 - 2 * t_3;
    float h11 = t_3 - t_2;

    float x0 = xs[i];
    float x1 = xs[i + 1];
    float y0 = ys[i];
    float y1 = ys[i + 1];

    float m0, m1;
    if (i == 0)
    {
        m0 = (ys[1] - ys[0]) / (xs[1] - xs[0]);
        m1 = (ys[2] - ys[0]) / (xs[2] - xs[0]);
    }
    else if (i == interp->n - 2)
    {
        m0 = (ys[interp->n - 1] - ys[interp->n - 3]) / (xs[interp->n - 1] - xs[interp->n - 3]);
        m1 = (ys[interp->n - 1] - ys[interp->n - 2]) / (xs[interp->n - 1] - xs[interp->n - 2]);
    }
    else
    {
        m0 = catmullSlope(xs, ys, interp->n, i);
        m1 = catmullSlope(xs, ys, interp->n, i + 1);
    }
    return h00 * y0 + h01 * y1 + h10 * (x1 - x0) * m0 + h11 * (x1 - x0) * m1;
}