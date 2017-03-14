#include "physics.h"

#define GRAVITY 8
#define DRAG 4

PhysicsPoint makePhysicsPoint(int x, int y, int xvel, int yvel) {
  PhysicsPoint pp;
  pp.pos.x = x;
  pp.pos.y = y;
  pp.vel.x = xvel;
  pp.vel.y = yvel;

  return pp;
}

void updatePhysicsPoint(PhysicsPoint* pp) {
  pp->pos.x += pp->vel.x/10;
  pp->pos.y += pp->vel.y/10;

  // Gravity
  pp->vel.y += GRAVITY;

  // Drag
  if (abs(pp->vel.x) > DRAG) {
    pp->vel.x = pp->vel.x + (pp->vel.x > 0 ? -1 : 1) * DRAG;
  } else {
    pp->vel.x = 0;
  }
}
