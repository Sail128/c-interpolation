
#include <stdio.h>
#include "cinterpolation.h"
#include <locale.h>

interpolate_t interp;
float xs[3] = {0.0, 10.0, 20.0};
float ys[3] = {0.0, 20.0, 25.0};

void main()
{
    setlocale(LC_NUMERIC, "French_Canada.1252");

    interp.edge = CLOSEST_POINT;
    interp.n = 3;
    interp.x = xs;
    interp.y = ys;

    for(float i=-1.0; i<22.0; i+=0.2){
        printf("%f  %f\n", i, interpolate_linear(&interp, i));
    }

}