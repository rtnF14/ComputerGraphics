#ifndef CLIPPING_H
#define CLIPPING_H

#include "point.h"
#include "color.h"
#include "math.h"

#define IS_COMPLETELY_INSIDE 1
#define IS_COMPLETELY_OUTSIDE 2
#define	IS_INTERSECT 3
#define BOTHZERO 4
#define BOTHONE 5
#define ONEZERO 6


typedef struct
{
	int xLeft;
	int xRight;
	int yTop;
	int yBottom;
} ClippingWindow;


typedef struct
{
	int left;
	int right;
	int top;
	int bottom;
} RegionCode;

typedef struct
{
	int resultStatusCode;
	int isLeftIntersection;
	int isRightIntersection;
	int isTopIntersection;
	int isBottomIntersection;
	int isStartPointCompletelyInside;
	int isEndPointCompletelyInside;
	Point startPoint;
	Point endPoint;
	RegionCode startPointRegionCode;
	RegionCode endPointRegionCode;
} LineAnalysisResult;


ClippingWindow setClippingWindow(int left, int right, int top, int bottom);
RegionCode initRegionCode();
RegionCode computeRegionCode(Point p, ClippingWindow cw);
LineAnalysisResult analyzeLine(Point startPoint, Point endPoint, ClippingWindow cw);
LineAnalysisResult initLineAnalysisResult();
void printRegionCode(RegionCode rc);
int checkRegionCodeBit(int a, int b);
int isPointCompletelyInside(RegionCode x);
int isCompletelyInside(LineAnalysisResult x);
int isCompletelyOutside(LineAnalysisResult x);
void clipLine(LineAnalysisResult lar1, ClippingWindow cw1 , Point * output);



#endif