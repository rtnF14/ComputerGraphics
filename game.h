#ifndef GAME_H
#define GAME_H

#include "point.h"
#include "color.h"
#include "transform.h"

Point explosionPoint[11];
int planeloc;
int endSign;
void buildCannon(int x, int y, Color c);
void shootCannon();
void drawBaling(int x, int y, int rotation);
void drawTire(Point P, int rot);
void drawPlane(Point p, int direction, Color planeColor);
void drawBrokenPlaneCockpit(Point lastPoint);
void drawBrokenPlaneBody(Point lastPoint);
void drawBrokenPlaneWings(Point lastPoint);
void drawParachute(Point anc);
void drawTank(Point anc);
void drawRect(int x, int y, int w, int h, Color c);

#endif
