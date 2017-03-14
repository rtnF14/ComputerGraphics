#include "clipping.h"

ClippingWindow setClippingWindow(int left, int right, int top, int bottom){
	ClippingWindow temp;
	temp.xLeft = left;
	temp.xRight = right;
	temp.yTop = top;
	temp.yBottom = bottom;
	return temp;
}

void printRegionCode(RegionCode rc){
	printf("%d %d %d %d ---", rc.top, rc.bottom,rc.right, rc.left);
}

RegionCode initRegionCode(){
	RegionCode temp;
	temp.left = 0;
	temp.right = 0;
	temp.top = 0;
	temp.bottom = 0;
	return temp;
}

int checkRegionCodeBit(int a, int b){
	if (a == 0) {
		if (b == 0) return BOTHZERO;
		return ONEZERO;
	}
	else if (a == 1) {
		if (b == 1) return BOTHONE;
		return ONEZERO;
	}
}

RegionCode computeRegionCode(Point p, ClippingWindow cw){
	RegionCode temp =  initRegionCode();
	if (p.x < cw.xLeft) temp.left = 1;
	if (p.x > cw.xRight) temp.right = 1;
	if (p.y > cw.yTop) temp.top = 1;
	if (p.y < cw.yBottom) temp.bottom = 1;
	return temp;
}

int isPointCompletelyInside(RegionCode x) {
	return ((x.top == 0) && (x.left == 0) && (x.right == 0) && (x.bottom == 0));
}

int isCompletelyInside(LineAnalysisResult x){
	return ((x.isTopIntersection == BOTHZERO) && (x.isLeftIntersection == BOTHZERO) && (x.isRightIntersection == BOTHZERO) && (x.isBottomIntersection == BOTHZERO));
}

int isCompletelyOutside(LineAnalysisResult x){
	return ((x.isBottomIntersection == BOTHONE) || (x.isTopIntersection == BOTHONE) || (x.isLeftIntersection == BOTHONE) || (x.isRightIntersection == BOTHONE));
}


LineAnalysisResult analyzeLine(Point startPoint, Point endPoint, ClippingWindow cw){
	RegionCode startPointRegionCode = computeRegionCode(startPoint,cw);
	RegionCode endPointRegionCode = computeRegionCode(endPoint,cw);

	LineAnalysisResult result;
	result.isTopIntersection = checkRegionCodeBit(startPointRegionCode.top, endPointRegionCode.top);
	result.isBottomIntersection = checkRegionCodeBit(startPointRegionCode.bottom , endPointRegionCode.bottom);
	result.isLeftIntersection = checkRegionCodeBit(startPointRegionCode.left, endPointRegionCode.left);
	result.isRightIntersection = checkRegionCodeBit(startPointRegionCode.right , endPointRegionCode.right);

	result.isStartPointCompletelyInside = isPointCompletelyInside(startPointRegionCode);
	result.isEndPointCompletelyInside = isPointCompletelyInside(endPointRegionCode);

	result.startPoint = startPoint;
	result.endPoint = endPoint;

	result.startPointRegionCode = startPointRegionCode;
	result.endPointRegionCode = endPointRegionCode;

	return result;
}


void clipLine(LineAnalysisResult lar1, ClippingWindow cw1 , Point * output) {

	Color white = setColor(255,255,255);
	Point line[2];
	line[0] = makePoint(lar1.startPoint.x , lar1.startPoint.y);
	line[1] = makePoint(lar1.endPoint.x, lar1.endPoint.y);

	if (isCompletelyInside(lar1)) {
		drawPolygon(2,line,white,1);
		output[0] = makePoint(lar1.startPoint.x , lar1.startPoint.y);
		output[1] = makePoint(lar1.endPoint.x, lar1.endPoint.y);
	 }
	else if (isCompletelyOutside(lar1)) {
		output[0] = makePoint(0 , 0);
		output[1] = makePoint(0, 0);
	}
	else
	{

		//top intersection
		if( lar1.isTopIntersection == ONEZERO) {
			//start point adjust
			if(lar1.startPointRegionCode.top) {
				if ( lar1.startPoint.x == lar1.endPoint.x) {
					lar1.startPoint.y = cw1.yTop;
				}
				else {
					double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
					double newX = lar1.startPoint.x + ((cw1.yTop - lar1.startPoint.y) / m);
					lar1.startPoint.x = round(newX);
					lar1.startPoint.y = cw1.yTop;
				}
				if ((lar1.startPoint.x >= cw1.xLeft) && (lar1.startPoint.x <= cw1.xRight)) {
					lar1.startPointRegionCode = initRegionCode();
				}
			}

			//end point adjust
			if(lar1.endPointRegionCode.top) {
				if ( lar1.startPoint.x == lar1.endPoint.x) {
					lar1.startPoint.y = cw1.yTop;
				}
				else {
					double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
					double newX = lar1.endPoint.x + ((cw1.yTop - lar1.endPoint.y) / m);
					lar1.endPoint.x = round(newX);
					lar1.endPoint.y = cw1.yTop;
				}
				if ((lar1.endPoint.x >= cw1.xLeft) && (lar1.endPoint.x <= cw1.xRight)){
					lar1.endPointRegionCode = initRegionCode();
				}
			}
		}


		//bottom slice
		if( lar1.isBottomIntersection == ONEZERO) {
			//start point adjust
			if(lar1.startPointRegionCode.bottom) {
				if ( lar1.startPoint.x == lar1.endPoint.x) {
					lar1.startPoint.y = cw1.yBottom;
				}
				else {
					double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
					double newX = lar1.startPoint.x + ((cw1.yBottom - lar1.startPoint.y) / m);
					lar1.startPoint.x = round(newX);
					lar1.startPoint.y = cw1.yBottom;
				}
				if ((lar1.startPoint.x >= cw1.xLeft) && (lar1.startPoint.x <= cw1.xRight)){
					lar1.startPointRegionCode = initRegionCode();
				}
			}

			//end point adjust
			if(lar1.endPointRegionCode.bottom) {

				if ( lar1.startPoint.x == lar1.endPoint.x) {
					lar1.endPoint.y = cw1.yBottom;
				}
				else {
					double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
					double newX = lar1.endPoint.x + ( (cw1.yBottom - lar1.endPoint.y) / m);
					lar1.endPoint.x = round(newX);
					lar1.endPoint.y = cw1.yBottom;
				}
				if ((lar1.endPoint.x >= cw1.xLeft) && (lar1.endPoint.x <= cw1.xRight)){
					lar1.endPointRegionCode = initRegionCode();
				}
			}
		}



		//left slice
		if ( lar1.isLeftIntersection == ONEZERO) {

			//start point adjust
			if(lar1.startPointRegionCode.left) {
				double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
				double newY = (double) lar1.startPoint.y +  (m *((double) cw1.xLeft - (double) lar1.startPoint.x));
				lar1.startPoint.x = cw1.xLeft;
				lar1.startPoint.y = round(newY);
				if ((lar1.startPoint.x >= cw1.yBottom) && (lar1.startPoint.x <= cw1.yTop)){
					lar1.startPointRegionCode = initRegionCode();
				}
			}

			//end point adjust
			if(lar1.endPointRegionCode.left) {
				double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
				double newY = (double) lar1.endPoint.y +  (m *( (double) cw1.xLeft - (double) lar1.endPoint.x ));
				lar1.endPoint.x = cw1.xLeft;
				lar1.endPoint.y = round(newY);
				if ((lar1.endPoint.x >= cw1.yBottom) && (lar1.endPoint.x <= cw1.yTop)){
					lar1.endPointRegionCode = initRegionCode();
				}
			}
		}


		//right slice
		if ( lar1.isRightIntersection == ONEZERO) {
			//start point adjust
			if(lar1.startPointRegionCode.right) {
				double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
				double newY = (double) lar1.startPoint.y +  (m *((double)cw1.xRight - (double)lar1.startPoint.x ));
				lar1.startPoint.x = cw1.xRight;
				lar1.startPoint.y = round(newY);

			}

			//end point adjust
			if(lar1.endPointRegionCode.right) {
				double m =  (((double)lar1.startPoint.y - (double) lar1.endPoint.y)  / (  (double) lar1.startPoint.x - (double) lar1.endPoint.x) );
				double newY = (double) lar1.endPoint.y +  (m *((double) cw1.xRight -(double) lar1.endPoint.x  ));
				lar1.endPoint.x = cw1.xRight;
				lar1.endPoint.y = round(newY);
			}
		}

		line[0] = makePoint(lar1.startPoint.x , lar1.startPoint.y);
		line[1] = makePoint(lar1.endPoint.x, lar1.endPoint.y);
		output[0] = makePoint(lar1.startPoint.x , lar1.startPoint.y);
		output[1] = makePoint(lar1.endPoint.x, lar1.endPoint.y);

	}
}