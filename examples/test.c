
#include <stdio.h>
#include "cinterpolation.h"
#include <locale.h>

interpolate_t interp;
float xs[3] = {0.0, 10.0, 20.0};
float ys[3] = {0.0, 20.0, 25.0};

void main()
{
    setlocale(LC_NUMERIC, "French_Canada.1252"); // just here so I can paste the values in excel

    interp.edge = CLOSEST_POINT;
    interp.n = 3;
    interp.x = xs;
    interp.y = ys;

    for(float i=-1.0; i<22.0; i+=0.2){
        printf("%f  %f\n", i, interpolate_linear(&interp, i));
    }

    float x2s[8] = {0.0, 3.0, 6.0, 7.0, 8.0, 14.0, 17.0, 20.0};
    float y2s[8] = {0.0, 5.0, 6.0, 8.0, 5.0, 14.0, 17.0, 20.0};

    interp.n = 8;
    interp.x = x2s;
    interp.y = y2s;

    printf("catmul spline\n");
    for(float i=-1.0; i<22.0; i+=0.05){
        printf("%f  %f\n", i, interpolate_catmulspline(&interp, i));
    }


}