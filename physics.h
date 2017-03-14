#ifndef PHYSICS_H
#define PHYSICS_H

#include "point.h"

//physics point
typedef struct {
  Point pos;
  Point vel;
} PhysicsPoint;

PhysicsPoint makePhysicsPoint(int x, int y, int xvel, int yvel);
void updatePhysicsPoint(PhysicsPoint* pp);


#endif