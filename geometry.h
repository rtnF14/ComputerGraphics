#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "point.h"
#include "color.h"

void drawBresenhamLine (Point P1, Point P2, Color C, int W);
void drawPolyline (int n, Point *P, Color C, int W);
void drawPolygon (int n, Point *P, Color C, int W);
void drawExplosion (Point initialPoint, int n, Point *P, int scaleFactor);
void drawCircle (int radius, Point P, int W, Color C);
void drawCircleHalf (int radius, Point P, int W, Color C);
void drawRect(int x, int y, int w, int h, Color c);


#endif