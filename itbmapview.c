#include "grafika.h"
#include "color.h"
#include "point.h"
#include "framebuffer.h"
#include "geometry.h"
#include "transform.h"
#include "filling.h"
#include "clipping.h"
#include "keypress.h"



double left = 0;
double up = 0;
double scaleFactor = 1;
int rotationDegree = 0;
int rotationDegreeText = 0;
unsigned char drawBuildings = 1;
unsigned char drawRoads = 1;
unsigned char drawTrees = 1;
pthread_t keypressListener;

unsigned char between(int a, int b, int x) {
	return x > a && x < b;
}

unsigned char isLineSane(int n, Point* line) {
	for (size_t i = 0; i < n; i++) {
		// Should be fine for a few years
		if (!between(-50000, 100000, line[i].x) || !between(-50000, 100000, line[i].y)) return 0;
	}
	return 1;
}

void refreshFromFile (const char* filename, unsigned char isPoly, Color color) {
	
	FILE* fp = fopen(filename, "r");

	ClippingWindow cw1 = setClippingWindow(scaleFactor*(100+left),scaleFactor*(200+left),scaleFactor*(200+up),scaleFactor*(100+up));
	double xScalingFactor = (1000 - 500) / ( (scaleFactor*(200+left)) - (scaleFactor*(100+left)) );
	double yScalingFactor = (550 - 50) / ( scaleFactor*((200+left)) - scaleFactor*((100+left)));
	double xTranslation = (( (scaleFactor*(200+left)) * 500) - ( (scaleFactor*(100+left)) * 1000)) / ( (scaleFactor*(200+left)) - (scaleFactor*(100+left)));
	double yTranslation = (( (scaleFactor*(200+up)) * 50) - ( (scaleFactor*(100+up)) * 550)) / ( (scaleFactor*(200+up)) - (scaleFactor*(100+up)) );	

	while(!feof(fp)){
		
		int nPoints;
		fscanf(fp, "%d", &nPoints);
		Point * points = malloc(nPoints * sizeof(Point));

		
		int j;
		for(j = 0 ; j < nPoints ; j++) fscanf(fp, "%d %d", &points[j].x, &points[j].y); 

		if (isPoly) drawPolygon(j,points,color,1);
		else drawPolyline(j,points,color,1);

		for (j = 0 ; j < (isPoly ? nPoints : nPoints - 1) ;j++){
			int lawan = (j+1);
			if (j == (nPoints-1)) lawan = 0;

			LineAnalysisResult lar1;
			//kasus khusus kalau menaik vertikal
			if ((points[j].x == points[lawan].x) && (points[lawan].y > points[j].y)) {
					lar1 = analyzeLine(points[lawan] , points[j], cw1);
			}
			else {
					lar1 = analyzeLine(points[j] , points[lawan], cw1);
			}
			Point clippedLine[2];
			clipLine(lar1,cw1,clippedLine);
			if (isLineSane(2, clippedLine)) {
				drawPolyline(2,clippedLine,setColor(255,0,0),1);
				ScaleLine(clippedLine,xScalingFactor,yScalingFactor);
				TranslationLine(clippedLine,xTranslation,yTranslation);

				drawPolyline(2,clippedLine,color,1);

			}
		}
		free(points);
	}
	close(fileno(fp));
}


//redraw framebuffer
void refreshScreen() 
{

	printBackground(setColor(0,0,0));

	// Point clippingWindow[4];
	Point *clippingWindow;
	Point *tes;
	Point center;
	clippingWindow = (Point *) malloc(4 * sizeof(Point));
	clippingWindow[0] = makePoint(scaleFactor*(100+left),scaleFactor*(100+up));
	clippingWindow[1] = makePoint(scaleFactor*(100+left),scaleFactor*(200+up));
	clippingWindow[2] = makePoint(scaleFactor*(200+left),scaleFactor*(200+up));
	clippingWindow[3] = makePoint(scaleFactor*(200+left),scaleFactor*(100+up));
	center = makePoint(scaleFactor*(150+left),scaleFactor*(150+up));
	if (rotationDegree > 0) {
		tes = rotateMany(center, clippingWindow, rotationDegree, 4);
		int i;
		for(i = 0; i < 4; i++) {
			clippingWindow[i] = tes[i];
		}
	}
	drawPolygon(4,clippingWindow,setColor(0,180,180),4);
	
	Point viewingWindow[4];
	
	viewingWindow[0] = makePoint(500,50);
	viewingWindow[1] = makePoint(500,550);
	viewingWindow[2] = makePoint(1000,550);
	viewingWindow[3] = makePoint(1000,50);
	
	
	drawPolygon(4,viewingWindow,setColor(0,255,180),1);

	if (drawBuildings) refreshFromFile("building.txt", 1, setColor(255,255,255));
	if (drawRoads) refreshFromFile("jalan.txt", 0,setColor(255,255,0));
	if (drawTrees) refreshFromFile("pohon.txt", 1,setColor(0,255,0));

}



//keypress listener in separate thread
void *keypressListen(void *x_void_ptr) {
	 int cmd = ' ';
	 while (1) 
	 {
	 	cmd = getch();
	 	if (cmd == LEFT_KEYPRESS) { left -= 20; refreshScreen();}
	    else if ( cmd == RIGHT_KEYPRESS) {	left+= 20;refreshScreen();	}
	    else if ( cmd == UP_KEYPRESS ) {up += 20; refreshScreen();}
	    else if ( cmd == DOWN_KEYPRESS ) {up -= 20; refreshScreen();}
	    else if ( cmd == ZOOMIN_KEYPRESS) {scaleFactor -= 0.1; refreshScreen();}
	    else if ( cmd == ZOOMOUT_KEYPRESS) {scaleFactor += 0.1; refreshScreen();}
	    else if ( cmd == TOGGLE_BUILDING_KEYPRESS) {drawBuildings = !drawBuildings; refreshScreen();}
	    else if ( cmd == TOGGLE_ROADS_KEYPRESS) {drawRoads = !drawRoads; refreshScreen();}
	    else if ( cmd == TOGGLE_TREES_KEYPRESS) {drawTrees = !drawTrees; refreshScreen();}
	    else if ( cmd == ROTATE_KEYPRESS) {
	    	rotationDegree = (rotationDegree + 10) % 360;
	    	refreshScreen();}
	}
	return NULL;
}

//prevents exiting program
void programBarrier(){
	while(1) {}
}

void showSplashScreen() {
	//Initiate Splash Screen Component
	Point * hurufI = (Point*) malloc(5 * sizeof(Point));
	Point * hurufT = (Point*) malloc(9 * sizeof(Point));
	Point * hurufB = (Point*) malloc(7 * sizeof(Point));
	Point * detailHurufB1 = (Point*) malloc(5 * sizeof(Point));
	Point * detailHurufB2 = (Point*) malloc(5 * sizeof(Point));
	Point * bintang = (Point*) malloc (5 * sizeof(Point));

	int baseX = 400;
	int baseY = 300;
	//center = base+min+((max-min)/2)
	Point centerI;
	Point centerT;
	Point centerB;
	Point centerB1;
	Point centerB2;
	int isBounce = 0;
	int iteration = 0;
	while (1) {
		hurufI[0].x = baseX + 25; hurufI[0].y = baseY;
		hurufI[1].x = baseX + 50; hurufI[1].y = baseY;
		hurufI[2].x = baseX + 50; hurufI[2].y = baseY + 100;
		hurufI[3].x = baseX + 25; hurufI[3].y = baseY + 100;
		hurufI[4].x = baseX + 25; hurufI[4].y = baseY;
		rotationDegreeText = (rotationDegreeText+10)%360;
		centerI.x = baseX+37; centerI.y = baseY+50;
		hurufI = rotateMany(centerI,hurufI,rotationDegreeText,5);

		hurufT[0].x = baseX + 70; hurufT[0].y = baseY;
		hurufT[1].x = baseX + 145; hurufT[1].y = baseY;
		hurufT[2].x = baseX + 145; hurufT[2].y = baseY + 20;
		hurufT[3].x = baseX + 115; hurufT[3].y = baseY + 20;
		hurufT[4].x = baseX + 115; hurufT[4].y = baseY + 100;
		hurufT[5].x = baseX + 100; hurufT[5].y = baseY + 100;
		hurufT[6].x = baseX + 100; hurufT[6].y = baseY + 20;
		hurufT[7].x = baseX + 70; hurufT[7].y = baseY + 20;
		hurufT[8].x = baseX + 70; hurufT[8].y = baseY;
		centerT.x = baseX+107; centerT.y = baseY+60;
		hurufT = rotateMany(centerT,hurufT,rotationDegreeText,9);

		hurufB[0].x = baseX + 165; hurufB[0].y = baseY;
		hurufB[1].x = baseX + 215; hurufB[1].y = baseY;
		hurufB[2].x = baseX + 215; hurufB[2].y = baseY + 50;
		hurufB[3].x = baseX + 265; hurufB[3].y = baseY + 50;
		hurufB[4].x = baseX + 265; hurufB[4].y = baseY + 100;
		hurufB[5].x = baseX + 165; hurufB[5].y = baseY + 100;
		hurufB[6].x = baseX + 165; hurufB[6].y = baseY;
		centerB.x = baseX+215; centerB.y=baseY+75;
		hurufB = rotateMany(centerB,hurufB,rotationDegreeText,7);

		detailHurufB1[0].x = baseX + 180; detailHurufB1[0].y = baseY + 20;
		detailHurufB1[1].x = baseX + 180; detailHurufB1[1].y = baseY + 40;
		detailHurufB1[2].x = baseX + 200; detailHurufB1[2].y = baseY + 40;
		detailHurufB1[3].x = baseX + 200; detailHurufB1[3].y = baseY + 20;
		detailHurufB1[4].x = baseX + 180; detailHurufB1[4].y = baseY + 20;
		// centerB1.x = baseX+190; centerB1.y = baseY+30;
		detailHurufB1 = rotateMany(centerB,detailHurufB1,rotationDegreeText,5);

		detailHurufB2[0].x = baseX + 180; detailHurufB2[0].y = baseY + 65;
		detailHurufB2[1].x = baseX + 180; detailHurufB2[1].y = baseY + 85;
		detailHurufB2[2].x = baseX + 250; detailHurufB2[2].y = baseY + 85;
		detailHurufB2[3].x = baseX + 250; detailHurufB2[3].y = baseY + 65;
		detailHurufB2[4].x = baseX + 180; detailHurufB2[4].y = baseY + 65;
		// centerB2.x = baseX+215; centerB2.y = baseY+75;
		detailHurufB2 = rotateMany(centerB,detailHurufB2,rotationDegreeText,5);

		if (hurufB[3].x >= displayWidth) {
			isBounce = 1;
			iteration++;
		}
		if (hurufI[0].x <= 0) {
			isBounce = 0;
			iteration++;
		}
		if (isBounce == 0) {
			baseX += 100;
		} else {
			baseX -= 100;
		}
		drawPolyline(5, hurufI, setColor(255,255,255), 1);
		floodFill(centerI.x, centerI.y, setColor(255,0,0), setColor(0,0,0));
		drawPolyline(9, hurufT, setColor(255,255,255), 1);
		floodFill(centerT.x, centerT.y, setColor(0,255,0), setColor(0,0,0));
		drawPolyline(7, hurufB, setColor(255,255,255), 1);
		floodFill(centerB.x, centerB.y, setColor(0,0,255), setColor(0,0,0));
		drawPolyline(5, detailHurufB1, setColor(255,255,255), 1);
		drawPolyline(5, detailHurufB2, setColor(255,255,255), 1);
		printBackground(setColor(0,0,0));
		if (iteration == 3) {
			break;
		}
	}
}

int main() {
	initScreen();
	printBackground(setColor(0,0,0));
	//showSplashScreen();
	printBackground(setColor(0,0,0));
	refreshScreen();
	pthread_create(&keypressListener, NULL, keypressListen, NULL);
	programBarrier();
	terminate();
	return 0;
}
