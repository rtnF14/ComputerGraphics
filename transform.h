#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "point.h"

Point rotatePoint(Point p ,Point pivot, float angle);
Point* rotateMany(Point p, Point* p1, double angle, int length);
void ScaleLine(Point * p , double scalingFactorX , double scalingFactorY );
void TranslationLine(Point *  p , int xTranslation, int yTranslation);

#endif
