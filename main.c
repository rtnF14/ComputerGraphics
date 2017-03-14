#include "grafika.h"

int endSign = 0;
int left= 100;
int planeloc = 0;

uint64_t getTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}


/* this function is run by the second thread */
void *keypressListen(void *x_void_ptr) {
	 int cmd = ' ';
	 while (1) {
	 	cmd = getch();
	 	if (cmd == ENTER_KEYPRESS) { shootCannon();}  
    else if (cmd == LEFT_KEYPRESS) { left -= 50;} 
    else if (cmd == RIGHT_KEYPRESS) {	left+= 50;	}
	}
	return NULL;
}

int main()
{
  int x = 0, y = 0;
  int i, j;
  int sign;
  long int location = 0;
  Color X = setColor(0,0,0);
  Color C = setColor(255,255,10);
  Color bgColor = setColor(66,134,244);

  initScreen();
 	printBackground(bgColor);


  //keypress
 	pthread_t keypressListener;
	if(pthread_create(&keypressListener, NULL, keypressListen, &x)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}

	int counter = 0;
	i = 120;
	j = 150;
	sign = 1;
  int ysign = 1;

	while (!endSign){
    uint64_t start = getTimeStamp();

    i += 8 * sign;
    j += 8 * ysign;

    if (i > displayWidth-200) { sign = -1; } 
    else if (i < 100) { sign = 1;  }

    if (j > 200) { sign = -1; } 
    else if (j < 100) { ysign = 1; } 

    printBackground(bgColor);
  	drawPlane(makePoint(i, j), -sign, X);
		planeloc = i;
	    buildCannon(left, displayHeight-100, C);

    uint64_t end = getTimeStamp();
    if (end-start < 33000) usleep(33000-(end-start));
	}


	int sf = 1;
  PhysicsPoint parachute = makePhysicsPoint(i, j-200, -100*sign, -100);
  PhysicsPoint brokenPlaneCockpit = makePhysicsPoint(i, j, 100*sign, -50);
  PhysicsPoint brokenPlaneBody = makePhysicsPoint(i, j, 100*sign, 0);
  PhysicsPoint brokenPlaneWings = makePhysicsPoint(i, j, 0, -50);
  PhysicsPoint baling = makePhysicsPoint(i-40, j+10, -100*sign, 0);

  char hasBounced = 0;

  int bb_x = i - 60;
  int bb_y = j + 100;
  int bb_w = 200;
  int bb_h = 200;

	while (brokenPlaneWings.pos.y < displayHeight - 100 || !hasBounced) {
    	printBackground(bgColor);
    	if (sf < 5) {
    	    //drawExplosion(makePoint(i, 240), 11, explosionPoint, sf);
    	    sf++;
    	}
      updatePhysicsPoint(&parachute);
      updatePhysicsPoint(&brokenPlaneCockpit);
      updatePhysicsPoint(&brokenPlaneBody);
      updatePhysicsPoint(&brokenPlaneWings);
      updatePhysicsPoint(&baling);

      if (brokenPlaneWings.pos.y > displayHeight - 100 && !hasBounced) {
        hasBounced = 1;
        brokenPlaneWings.pos.y = displayHeight - 150;
        brokenPlaneWings.vel.x = 0;
        brokenPlaneWings.vel.y = -200;
      }

	    //drawBrokenPlaneCockpit(brokenPlaneCockpit.pos);
	    //drawBrokenPlaneBody(brokenPlaneBody.pos);
	    drawBrokenPlaneWings(brokenPlaneWings.pos);
	    //drawParachute(parachute.pos);
      //drawBaling(baling.pos.x, baling.pos.y, baling.pos.y);

      drawRect(0, 0, displayWidth, bb_y, X);
      drawRect(0, bb_y, bb_x, bb_h, X);
      drawRect(bb_x + bb_w, bb_y, displayWidth - bb_x - bb_w, bb_h, X);
      drawRect(0, bb_y + bb_h, displayWidth, displayHeight - bb_y - bb_h, X);

	    usleep(33000);
	}



  terminate();
	   
}
