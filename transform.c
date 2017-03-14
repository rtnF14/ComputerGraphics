#include "transform.h"

#define PI acos(-1)

Point rotatePoint(Point p ,Point pivot, float angle){
	float s = sin(angle * PI / 180.0);
	float c = cos(angle * PI / 180.0);
	p.x -= pivot.x;
	p.y -= pivot.y;

	int xnew = (int) (p.x * c - p.y * s);
	int ynew = (int) (p.x * s + p.y * c);

	p.x = xnew + pivot.x;
	p.y = ynew + pivot.y;
	return p;

}

//return rotated muliple point
Point* rotateMany(Point p, Point* p1, double angle, int length) {
  Point *temp = (Point*) malloc(length*sizeof(Point));
  for (int i = 0; i < length; i++) {
    temp[i] = rotatePoint(p1[i], p, angle);
  }
  return temp;
}



void ScaleLine(Point * p , double scalingFactorX , double scalingFactorY ){
    double xtemp = (double) p[0].x * scalingFactorX;
    double ytemp = (double) p[0].y * scalingFactorY;
    double xtemp1 = (double) p[1].x * scalingFactorX;
    double ytemp1 = (double) p[1].y * scalingFactorY;

    p[0].x = round(xtemp);
    p[0].y = round(ytemp);
    p[1].x = round(xtemp1);
    p[1].y = round(ytemp1);
}

void TranslationLine(Point *  p , int xTranslation, int yTranslation ) {
    p[0].x += xTranslation;
    p[0].y += yTranslation;
    p[1].x += xTranslation;
    p[1].y += yTranslation;
}