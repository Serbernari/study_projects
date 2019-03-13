#ifndef HERMITCUBICSPLINE_H
#define HERMITCUBICSPLINE_H

#include <stdio.h>
#include <vector>
#include <array>
#include <cmath>

typedef std::vector<float> TPointList1D;
typedef std::vector<std::array<float,2>> TPointList2D;

// t is a value that goes from 0 to 1 to interpolate in a C1 continuous way across uniformly sampled data points.
// when t is 0, this will return B.  When t is 1, this will return C.
float CubicHermite (float A, float B, float C, float D, float x);

#endif // HERMITCUBICSPLINE_H
