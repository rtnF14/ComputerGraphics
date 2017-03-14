#include "geometry.h"


/*Gambar explosion masih jelek*/
Point explosionPoint[11] = {
	{4,9}, {7,12}, {11, 10}, {7, 14}, {10, 16},
	{6, 16}, {2, 18}, {5, 15}, {1, 14}, {4, 12}
};

void swap (int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void swapPoint (Point *P1, Point *P2) {
	swap(&P1->x, &P2->x);
	swap(&P1->y, &P2->y);
}

void plotSlopPositiveLine (Point P1, Point P2, Color C, int W) {
	int dX, dY, p;
	int i, j, x, y;

	dX = abs(P2.x - P1.x);
	dY = abs(P2.y - P1.y);
	i = P1.x;
	j = P1.y;

	if (dX >= dY) {
		p = 2*dY - dX;
		// printf("Based on +X\n");
		for (x=P1.x; x<=P2.x; x++) {
			// printf("%d %d\n", x, j);
			if (W<4) setXY(W, x, j, C);
			else {
				if (x%(W/2)==0) setXY(W, x, j, C);
			}
			if (p >= 0) {
				p += 2* (dY - dX);
				i++;
				j++;
			}
			else {
				p += 2*dY;
				i++;
			}
		}
	}
	else {
		p = 2*dX - dY;
		// printf("Based on +Y\n");
		for (y=P1.y; y<=P2.y; y++) {
			// printf("%d %d\n", i, y);
			if (W<4) setXY(W, i, y, C);
			else {
				if (y%(W/2)==0) setXY(W, i, y, C);
			}
			if (p >= 0) {
				p += 2* (dX - dY);
				i++;
				j++;
			}
			else {
				p += 2*dX;
				j++;
			}
		}
	}
}

void plotSlopNegativeLine (Point P1, Point P2, Color C, int W) {
	int dX, dY, p;
	int i, j, x, y;

	dX = abs(P2.x - P1.x);
	dY = abs(P2.y - P1.y);
	i = P1.x;
	j = P1.y;

	if (dX >= dY) {
		p = 2*dY - dX;
		// printf("Based on -X\n");
		for (x=P1.x; x<=P2.x; x++) {
			// printf("%d %d\n", x, j);
			if (W<4) setXY(W, x, j, C);
			else {
				if (x%(W/2)==0) setXY(W, x, j, C);
			}
			if (p >= 0) {
				p += 2* (dY - dX);
				i++;
				j--;
			}
			else {
				p += 2*dY;
				i++;
			}
		}
	}
	else {
		p = 2*dX - dY;
		i = P2.x;
		j = P2.y;
		// printf("Based on -Y\n");
		for (y=P2.y; y<=P1.y; y++) {
			// printf("%d %d\n", i, y);
			if (W<4) setXY(W, i, y, C);
			else {
				if (y%(W/2)==0) setXY(W, i, y, C);
			}
			if (p >= 0) {
				p += 2* (dX - dY);
				i--;
				j++;
			}
			else {
				p += 2*dX;
				j++;
			}
		}
	}
}

void plotVerticalLine (Point P1, Point P2, Color C, int W) {
	int j;

	if (P2.y < P1.y) {
		swapPoint(&P1,&P2);
	}

	for(j = P1.y ; j <= P2.y; j++){
		// printf("%d %d\n", P1.x , j);
		setXY(W, P1.x, j, C);
	}
}

void drawBresenhamLine (Point P1, Point P2, Color C, int W) {
	if (P1.x > P2.x) {
		swapPoint(&P1,&P2);
	}
	// printf("%d %d\n", P1.x, P1.y);
	// printf("%d %d\n", P2.x, P2.y);
	if ((P2.x >= P1.x && P1.y > P2.y)) {
		//printf("N Slope\n");
		plotSlopNegativeLine(P1,P2,C,W);
	}
	else if (P1.x == P2.x) {
		plotVerticalLine(P1,P2,C,W);
	}
	else {
		//printf("P Slope\n");
		plotSlopPositiveLine(P1,P2,C,W);
	}
}

void drawPolyline (int n, Point *P, Color C, int W) {
	int i;
	for (i = 0;i < n-1;i++) {
		drawBresenhamLine(P[i], P[i+1], C, W);
	}
}

/*
Procedure untuk menggambar polygon

n	: jumlah titik sudut polygon
P	: array of Point (titik-titik sudut)
C	: warna garis polygon
W	: weight (ketebalan) garis yang diinginkan
*/

void drawPolygon (int n, Point *P, Color C, int W) {
	drawPolyline(n, P, C, W);
	drawBresenhamLine(P[n-1], P[0], C, W);
}

/*
initialPoint : explosion location in the screen
scaleFactor : size of the explosion
*P isi dengan array explosionPoint
*/
void drawExplosion (Point initialPoint, int n, Point *P, int scaleFactor) {
	/*Orange Color*/
	Color C;
	C.R = 218;
	C.G = 114;
	C.B = 53;

	int i;

	if (scaleFactor >1) {
		for (i = 0; i<n; i++) {
			P[i].x *= scaleFactor;
			P[i].y *= scaleFactor;
		}
	}

	for (i = 0; i<n; i++) {
		P[i].x += initialPoint.x;
		P[i].y +=initialPoint.y;
	}

	drawPolygon(n, P, C, 2);
}

void plot8pixel (Point P, int p, int q, int W, Color C) {
    setXY(W, P.x+p, P.y+q, C);
    setXY(W, P.x-p, P.y+q, C);
    setXY(W, P.x+p, P.y-q, C);
    setXY(W, P.x-p, P.y-q, C);

    setXY(W, P.x+q, P.y+p, C);
    setXY(W, P.x-q, P.y+p, C);
    setXY(W, P.x+q, P.y-p, C);
    setXY(W, P.x-q, P.y-p, C);
}

void plot4pixel (Point P, int p, int q, int W, Color C) {
    //setXY(W, P.x+p, P.y+q, C);
    //setXY(W, P.x-p, P.y+q, C);
    setXY(W, P.x+p, P.y-q, C);
    setXY(W, P.x-p, P.y-q, C);

    //setXY(W, P.x+q, P.y+p, C);
    //setXY(W, P.x-q, P.y+p, C);
    setXY(W, P.x+q, P.y-p, C);
    setXY(W, P.x-q, P.y-p, C);
}

/*
radius	: jari-jari lingkaran
P	: titik asal lingkaran
*/
void drawCircle (int radius, Point P, int W, Color C) {
    int d, p, q;

    p = 0;
    q = radius;
    d = 3 - 2*radius;

    plot8pixel(P, p, q, W, C);

    while (p < q) {
        p++;
        if (d<0) {
            d = d + 4*p + 6;
        }
        else {
            q--;
            d = d + 4*(p-q) + 10;
        }

        plot8pixel(P, p, q, W, C);
    }
}


/*
radius	: jari-jari lingkaran
P	: titik asal lingkaran
*/
void drawCircleHalf (int radius, Point P, int W, Color C) {
    int d, p, q;

    p = 0;
    q = radius;
    d = 3 - 2*radius;

    plot4pixel(P, p, q, W, C);

    while (p < q) {
        p++;
        if (d<0) {
            d = d + 4*p + 6;
        }
        else {
            q--;
            d = d + 4*(p-q) + 10;
        }

        plot4pixel(P, p, q, W, C);
    }
}


void drawRect(int x, int y, int w, int h, Color c) {
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      setXY(1, x+i, y+j, c);
    }
  }
}