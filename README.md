# c-interpolation

functions to interpolate a list of values. 
Pet project for implementing various interpolation methods which can run on restricted environments(mcu's)

This library should work with platformio.

Raise an issue if you have improvement suggestions.

## TODO

- Add some actual unit testing
- Add general interpolate function
- Add more methods
- Non floating point methods

## usage

```C
interpolate_t interpolator;
float xs[3] = {0.0, 10.0, 20.0};
float ys[3] = {0.0, 20.0, 25.0};
interpolator.edge = CLOSEST_POINT;
interpolator.n = 3;
interpolator.x = xs;
interpolator.y = ys;

float y = interpolate_linear(&interpolator, x);

```

## License

Apache License version 2.0
