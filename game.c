#include "game.h"

typedef struct {
	Point body[4];
	Point bottom[6];
	Point tire1;
	Point tire2;
	Point tire3;
	Point tire4;
	Point tire5;
	Point circle;
	Color warnaTank;
	Color warnaBG;
} Tank;


typedef struct {
	Point cockpit[3];
	Point frontBody[4];
	Point backBody[3];
	Point leftRightWing[4];
	Point backWing[3];
} BrokenPlane;

typedef struct {
	Point halfcircle1;
	Point halfcircle2;
	Point halfcircle3;
	Point halfcircle4;
	Point halfcircle5;
	Point line1[2];
	Point line2[2];
	Point line3[2];
	Point line4[2];
	Point line5[2];
	Point line6[2];
	Point head;
	Point body[4];
	Point hands[4];
	Point legs[4];
	Color warnaParachute;
	Color warnaBG;
} Parachute;

void drawBaling(int x, int y, int rotation){
 		Point d[4];
	 	d[0].x = 20+x;
	 	d[0].y = 20+y;

	 	d[1].x = 23+x;
	 	d[1].y = 30+y;

	 	d[2].x = 20+x;
	 	d[2].y = 40+y;

	 	d[3].x = 17+x;
	 	d[3].y = 30+y;

	 	d[0] = rotatePoint(d[0],d[0],rotation);
	 	d[1] = rotatePoint(d[1],d[0],rotation);
	 	d[2] = rotatePoint(d[2],d[0],rotation);
	 	d[3] = rotatePoint(d[3],d[0],rotation);


	 	Point d_fp;
	 	d_fp.x = 20+x;
	 	d_fp.y = 30+y;

	 	drawPolygon(4,d,setColor(255,255,255),1);
	 	//floodFill(d_fp.x, d_fp.y, setColor(255,255,255) , getXY(d_fp.x, d_fp.y));


	 	Point d1[4];
	 	d1[0] = rotatePoint(d[0],d[0],180);
	 	d1[1] = rotatePoint(d[1],d[0],180);
	 	d1[2] = rotatePoint(d[2],d[0],180);
	 	d1[3] = rotatePoint(d[3],d[0],180);
	 	Point d1_fp=rotatePoint(d_fp,d[0],180);
	 	drawPolygon(4,d1,setColor(255,255,255),1);
	 	//floodFill(d1_fp.x, d1_fp.y, setColor(255,255,255) , getXY(d1_fp.x, d1_fp.y));


	 	Point d2[4];
	 	d2[0] = rotatePoint(d[0],d[0],90);
	 	d2[1] = rotatePoint(d[1],d[0],90);
	 	d2[2] = rotatePoint(d[2],d[0],90);
	 	d2[3] = rotatePoint(d[3],d[0],90);
	 	Point d2_fp;
	 	d2_fp = rotatePoint(d_fp,d[0],90);
	 	drawPolygon(4,d2,setColor(255,255,255),1);
	 	//floodFill(d2_fp.x, d2_fp.y, setColor(255,255,255) , getXY(d2_fp.x, d2_fp.y));

	 	Point d3[4];
	 	d3[0] = rotatePoint(d[0],d[0],-90);
	 	d3[1] = rotatePoint(d[1],d[0],-90);
	 	d3[2] = rotatePoint(d[2],d[0],-90);
	 	d3[3] = rotatePoint(d[3],d[0],-90);
	 	Point d3_fp = rotatePoint(d_fp,d[0],-90);
	 	drawPolygon(4,d3,setColor(255,255,255),1);
	 	//floodFill(d3_fp.x, d3_fp.y, setColor(255,255,255) , getXY(d3_fp.x, d3_fp.y));

 	}

void drawTire(Point P, int rot) {
	Color black = setColor(0,0,0);
	drawCircle(10, P, 4, black);
	Point velg[4];
	velg[0] = makePoint(P.x+9, P.y+1);
	velg[1] = makePoint(P.x-7, P.y+1);
	velg[2] = makePoint(P.x+1, P.y+9);
	velg[3] = makePoint(P.x+1, P.y-7);
	Point centre = makePoint(P.x+1, P.y+1);

	velg[0] = rotatePoint(velg[0], centre, rot);
	velg[1] = rotatePoint(velg[1], centre, rot);
	velg[2] = rotatePoint(velg[2], centre, rot);
	velg[3] = rotatePoint(velg[3], centre, rot);

	drawBresenhamLine(velg[0], velg[1], black, 2);
	drawBresenhamLine(velg[2], velg[3], black, 2);

		//drawBresenhamLine(velg[0], velg[1], black, 2);
		//drawBresenhamLine(velg[2], velg[3], black, 2);

}


void drawPlane(Point p, int direction, Color planeColor) {
  Point offset;
  offset.x = -1169;
  offset.y = -75;
  int mul = direction > 0 ? 1 : -1;

	//Color planeColor = setColor(25,25,25);
	//plane body
	Point d[6];
	d[0].x = p.x + (mul * (offset.x + 1250));
	d[0].y = p.y + ((offset.y + 50));
	d[1].x = p.x + (mul * (offset.x + 1100));
	d[1].y = p.y + ((offset.y + 50));
	d[2].x = p.x + (mul * (offset.x + 1054));
	d[2].y = p.y + ((offset.y + 90));
	d[3].x = p.x + (mul * (offset.x + 1285));
	d[3].y = p.y + ((offset.y + 90));
	d[4].x = p.x + (mul * (offset.x + 1285));
	d[4].y = p.y + ((offset.y + 25));
	d[5].x = p.x + (mul * (offset.x + 1250));
	d[5].y = p.y + ((offset.y + 50));
	drawPolygon(6,d,planeColor,2);
	floodFill(p.x + (mul * (offset.x + 1250)), p.y + ((offset.y + 55)), planeColor, getXY(p.x + (mul * (offset.x + 1250)), p.y + ((offset.y + 55))));


	//plane wing
	Point e[4];
	e[0].x = p.x + (mul * (offset.x + 1120));
	e[0].y = p.y + ((offset.y + 80));
	e[1].x = p.x + (mul * (offset.x + 1220));
	e[1].y = p.y + ((offset.y + 115));
	e[2].x = p.x + (mul * (offset.x + 1280));
	e[2].y = p.y + ((offset.y + 120));
	e[3].x = p.x + (mul * (offset.x + 1180));
	e[3].y = p.y + ((offset.y + 80));
	drawPolygon(4,e,planeColor,2);
	floodFill(p.x + (mul * (offset.x + 1220)), p.y + ((offset.y + 110))	 , planeColor, getXY(p.x + (mul * (offset.x + 1220)),p.y + ((offset.y + 110))));

	drawBaling(p.x -40 , p.y + 10 , p.x - 120);
	Point ptire = makePoint((p.x + (-mul*60)), p.y + 20);
	drawTire(ptire, p.x - 120);

}

void drawBrokenPlaneCockpit(Point lastPoint) {

	BrokenPlane brokenPlane;

	Color black = setColor(0,0,0);

	//plane pilot room - triangle
	brokenPlane.cockpit[0].x = lastPoint.x - 45;
	brokenPlane.cockpit[0].y = lastPoint.y + 15;

	brokenPlane.cockpit[1].x = lastPoint.x - 15;
	brokenPlane.cockpit[1].y = lastPoint.y - 50;

	brokenPlane.cockpit[2].x = lastPoint.x;
	brokenPlane.cockpit[2].y = lastPoint.y;


	drawPolygon(3, brokenPlane.cockpit, black, 2);
	floodFill(lastPoint.x - 10, lastPoint.y, black, getXY(lastPoint.x - 10, lastPoint.y));

	// front body - trapezoid
}

void drawBrokenPlaneBody(Point lastPoint) {

	BrokenPlane brokenPlane;

	Color black = setColor(0,0,0);

	brokenPlane.frontBody[0].x = lastPoint.x + 5;
	brokenPlane.frontBody[0].y = lastPoint.y - 7;

	brokenPlane.frontBody[1].x = lastPoint.x + 23;
	brokenPlane.frontBody[1].y = lastPoint.y - 45;

	brokenPlane.frontBody[2].x = lastPoint.x + 120;
	brokenPlane.frontBody[2].y = lastPoint.y;

	brokenPlane.frontBody[3].x = lastPoint.x + 60;
	brokenPlane.frontBody[3].y = lastPoint.y + 18;

	drawPolygon(4, brokenPlane.frontBody, black, 2);
	floodFill(lastPoint.x + 15, lastPoint.y - 15, black, getXY(lastPoint.x + 15, lastPoint.y - 15));

	// back body - triangle
	brokenPlane.backBody[0].x = lastPoint.x + 115;
	brokenPlane.backBody[0].y = lastPoint.y + 30;

	brokenPlane.backBody[1].x = lastPoint.x + 160;
	brokenPlane.backBody[1].y = lastPoint.y - 10;

	brokenPlane.backBody[2].x = lastPoint.x + 150;
	brokenPlane.backBody[2].y = lastPoint.y + 33;

	drawPolygon(3, brokenPlane.backBody, black, 2);
	floodFill(lastPoint.x + 135, lastPoint.y + 20, black, getXY(lastPoint.x + 135, lastPoint.y + 20));
}
	// left right wing - trapezoid
void drawBrokenPlaneWings(Point lastPoint) {

	BrokenPlane brokenPlane;

	Color black = setColor(0,0,0);

	brokenPlane.leftRightWing[0].x = lastPoint.x + 10 ;
	brokenPlane.leftRightWing[0].y = lastPoint.y + 70 ;

	brokenPlane.leftRightWing[1].x = lastPoint.x + 15;
	brokenPlane.leftRightWing[1].y = lastPoint.y + 100;

	brokenPlane.leftRightWing[2].x = lastPoint.x + 90;
	brokenPlane.leftRightWing[2].y = lastPoint.y + 95;

	brokenPlane.leftRightWing[3].x = lastPoint.x + 140;
	brokenPlane.leftRightWing[3].y = lastPoint.y + 60;

	drawPolygon(4, brokenPlane.leftRightWing, black, 2);
	floodFill(lastPoint.x + 80, lastPoint.y + 80, black, getXY(lastPoint.x + 80, lastPoint.y + 80));

	// back wing - triangle

	brokenPlane.backWing[0].x = lastPoint.x + 170;
	brokenPlane.backWing[0].y = lastPoint.y - 20;

	brokenPlane.backWing[1].x = lastPoint.x + 190;
	brokenPlane.backWing[1].y = lastPoint.y - 60;

	brokenPlane.backWing[2].x = lastPoint.x + 200;
	brokenPlane.backWing[2].y = lastPoint.y - 30;
	drawPolygon(3, brokenPlane.backWing, black, 2);
	floodFill(lastPoint.x + 180, lastPoint.y - 30, black, getXY(lastPoint.x + 180, lastPoint.y - 30));

}

void drawParachute(Point anc) {
	Parachute Par;
	Color black = setColor(0,0,0);
	Color pink = setColor(255,192,203);
	Color red = setColor(255,0,0);
	Color skin = setColor(255,220,177);

	Par.halfcircle1.x =anc.x-25;
	Par.halfcircle1.y =anc.y+100;

	Par.halfcircle2.x =anc.x-100;
	Par.halfcircle2.y =anc.y+100;

	Par.halfcircle3.x =anc.x-50;
	Par.halfcircle3.y =anc.y+100;

	Par.halfcircle4.x =anc.x;
	Par.halfcircle4.y =anc.y+100;

	Par.halfcircle5.x =anc.x+50;
	Par.halfcircle5.y =anc.y+100;

	Par.warnaParachute = black;
	Par.warnaBG = black;

	Par.line1[0].x = anc.x-125;
	Par.line1[0].y = anc.y+100;
	Par.line1[1].x = anc.x-25;
	Par.line1[1].y = anc.y+200;

	Par.line2[0].x = anc.x-75;
	Par.line2[0].y = anc.y+100;
	Par.line2[1].x = anc.x-25;
	Par.line2[1].y = anc.y+200;

	Par.line3[0].x = anc.x-25;
	Par.line3[0].y = anc.y+100;
	Par.line3[1].x = anc.x-25;
	Par.line3[1].y = anc.y+200;

	Par.line4[0].x = anc.x +25;
	Par.line4[0].y = anc.y+100;
	Par.line4[1].x = anc.x-25;
	Par.line4[1].y = anc.y+ 200;

	Par.line5[0].x = anc.x +75;
	Par.line5[0].y = anc.y+100;
	Par.line5[1].x = anc.x-25;
	Par.line5[1].y = anc.y+200;

	Par.line6[0].x = anc.x -25;
	Par.line6[0].y = anc.y+250;
	Par.line6[1].x = anc.x-25;
	Par.line6[1].y = anc.y+200;

	Par.head.x=anc.x-25;
	Par.head.y=anc.y+272;

	Par.body[0].x = anc.x-45;
	Par.body[0].y = anc.y+292;
	Par.body[1].x = anc.x-45;
	Par.body[1].y = anc.y+350;
	Par.body[2].x = anc.x-5;
	Par.body[2].y = anc.y+350;
	Par.body[3].x = anc.x-5;
	Par.body[3].y = anc.y+292;

	Par.hands[0].x = anc.x-45;
	Par.hands[0].y = anc.y+292;
	Par.hands[1].x = anc.x-30;
	Par.hands[1].y = anc.y+330;
	Par.hands[2].x = anc.x-5;
	Par.hands[2].y = anc.y+292;
	Par.hands[3].x = anc.x+10;
	Par.hands[3].y = anc.y+330;

	Par.legs[0].x = anc.x-45;
	Par.legs[0].y = anc.y+350;
	Par.legs[1].x = anc.x-55;
	Par.legs[1].y = anc.y+380;
	Par.legs[2].x = anc.x-5;
	Par.legs[2].y = anc.y+350;
	Par.legs[3].x = anc.x+5;
	Par.legs[3].y = anc.y+380;

	drawCircleHalf(100,Par.halfcircle1,2,black);
	drawCircleHalf(25,Par.halfcircle2,2,black);
	drawCircleHalf(25,Par.halfcircle3,2,black);
	drawCircleHalf(25,Par.halfcircle4,2,black);
	drawCircleHalf(25,Par.halfcircle5,2,black);
	floodFill(anc.x -25, anc.y + 50, pink, getXY(anc.x - 25, anc.y + 50));
	drawBresenhamLine(Par.line1[0],Par.line1[1],black,2);
	drawBresenhamLine(Par.line2[0],Par.line2[1],black,2);
	drawBresenhamLine(Par.line3[0],Par.line3[1],black,2);
	drawBresenhamLine(Par.line4[0],Par.line4[1],black,2);
	drawBresenhamLine(Par.line5[0],Par.line5[1],black,2);
	drawBresenhamLine(Par.line6[0],Par.line5[1],black,2);
	drawCircle(20,Par.head,2,black);
	floodFill(anc.x -40, anc.y + 275, skin, getXY(anc.x - 40, anc.y + 275));
	drawPolygon(4,Par.body,black,2);
	floodFill(anc.x -40, anc.y + 294, red, getXY(anc.x - 40, anc.y + 294));
	drawBresenhamLine(Par.hands[0],Par.hands[1],black,2);
	drawBresenhamLine(Par.hands[2],Par.hands[3],black,2);
	drawBresenhamLine(Par.legs[0],Par.legs[1],black,2);
	drawBresenhamLine(Par.legs[2],Par.legs[3],black,2);
}

void drawTank(Point anc) {

	Tank t;
	Color black = setColor(0,0,0);
	Color green = setColor(75, 83, 32);

	t.bottom[0].x = anc.x - 95;
	t.bottom[0].y = anc.y;
	t.bottom[1].x = anc.x + 105;
	t.bottom[1].y = anc.y;
	t.bottom[2].x = anc.x + 125;
	t.bottom[2].y = anc.y - 30;
	t.bottom[3].x = anc.x + 125;
	t.bottom[3].y = anc.y - 60;
	t.bottom[4].x = anc.x - 125;
	t.bottom[4].y = anc.y - 60;
	t.bottom[5].x = anc.x - 125;
	t.bottom[5].y = anc.y - 30;

	t.body[0].x = anc.x - 100;
	t.body[0].y = anc.y - 60;
	t.body[1].x = anc.x + 100;
	t.body[1].y = anc.y - 60;
	t.body[2].x = anc.x + 95;
	t.body[2].y = anc.y - 95;
	t.body[3].x = anc.x - 75;
	t.body[3].y = anc.y - 95;


	t.circle.x = anc.x + 15;
	t.circle.y = anc.y -95;

	t.tire1.x = anc.x;
	t.tire1.y = anc.y - 29;

	t.tire2.x = anc.x - 57;
	t.tire2.y = anc.y - 29;

	t.tire3.x = anc.x + 57;
	t.tire3.y = anc.y - 29;

	t.tire4.x = anc.x - 102;
	t.tire4.y = anc.y - 39;

	t.tire5.x = anc.x + 102;
	t.tire5.y = anc.y - 39;

	t.warnaTank = black;
	t.warnaBG = black;
	drawPolygon(6,t.bottom,black,2);
	floodFill(anc.x - 90, anc.y - 5, green, getXY(anc.x - 90, anc.y - 5));
	drawPolygon(4,t.body,black,2);
	floodFill(anc.x - 95, anc.y - 61, green, getXY(anc.x - 95, anc.y - 61));
	drawCircleHalf(50,t.circle,2,black);
	floodFill(anc.x + 15, anc.y - 99, green, getXY(anc.x + 15, anc.y - 99));
	drawCircle(25,t.tire1,2,black);
	floodFill(anc.x, anc.y - 32, black, getXY(anc.x, anc.y - 32));
	drawCircle(25,t.tire2,2,black);
	floodFill(anc.x - 57, anc.y - 32, black, getXY(anc.x - 57, anc.y - 32));
	drawCircle(25,t.tire3,2,black);
	floodFill(anc.x + 57, anc.y - 32, black, getXY(anc.x + 57, anc.y - 32));
	drawCircle(15,t.tire4,2,black);
	floodFill(anc.x - 102, anc.y - 42, black, getXY(anc.x - 102, anc.y - 42));
	drawCircle(15,t.tire5,2,black);
	floodFill(anc.x + 102, anc.y - 42, black, getXY(anc.x + 102, anc.y - 42));

}


int cannonX;
int cannonY;
int destProjectile;

void buildCannon(int x, int y, Color c) {
    cannonX = x;
    cannonY = y;
	drawTank(makePoint(x, y));
}

void shootCannon() {
	int y = cannonY - 12;
	int x = cannonX;
	Color black;
	black.R = 0;
	black.G = 0;
	black.B = 0;

	while ((y > 80) && (destProjectile == 0)) {
		Point head[3];
	    Point body[4];

	    head[0].x = x;
	    head[1].x = x - 10;
	    head[2].x = x + 10;
	    head[0].y = y;
	    head[1].y = y + 15;
	    head[2].y = y + 15;

	    drawPolygon(3, head, black, 2);
	    floodFill(x, y+4, setColor(125, 0, 125), getXY(x, y+4));

	    body[0].x = x - 15;
	    body[1].x = x - 15;
	    body[2].x = x + 15;
	    body[3].x = x + 15;
	    body[0].y = y + 16;
	    body[1].y = y + 40;
	    body[2].y = y + 40;
	    body[3].y = y + 16;

	    drawPolygon(4, body, black, 2);
	    floodFill(x, y+18, setColor(60, 0, 60), getXY(x, y+18));

		usleep(5000);
		y -= 4;
		if ((y < 240) && (y > 120) && (x > (planeloc-115)) && (x < (planeloc + 115))) {
		    destProjectile = 1;
		    endSign = 1;
		}
	}
}
