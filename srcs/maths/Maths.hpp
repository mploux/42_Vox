//
// Created by Marc on 12/04/2018.
//

#pragma once

#include <cmath>

#define M_PI 3.141592653589793238462643383279

#define ABS(x) (x < 0 ? -(x) : x)
#define DTR(angle) (angle * M_PI / 180)
#define LERP(a, b, n) (a + (b - a) * n)
