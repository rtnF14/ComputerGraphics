#ifndef FILLING_H
#define FILLING_H

#include "point.h"
#include "color.h"
#include "framebuffer.h"
#include "pointqueue.h"

void floodFill(int fp_x, int fp_y, Color C, Color fc);

#endif