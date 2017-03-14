#include "filling.h"



/*
Procedure floodfill

fp_x	: fire point x
fp_y	: fire point y
C	: warna flood
fc	: warna dasar yang akan ditimpa oleh warna flood
*/

void floodFill(int fp_x, int fp_y, Color C, Color fc) {

    if (isColorSame(C, fc)) {
        return;
    }

    queue pq_d;
    queue* pq = &pq_d;

    initQueue(pq);

    insertPoint(pq, makePoint(fp_x, fp_y));

    setXY(1, fp_x, fp_y, C);

    while(!queueEmpty(pq)) {
        Point p = nextPoint(pq);
        if ((p.x>=0) && (p.x<(vinfo.xres-1)) && (p.y>=0) && (p.y<(vinfo.yres-7))) {
            if (isColorSame(fc, getXY(p.x, p.y-1)) == 1) {
                setXY(1, p.x, p.y-1, C);
                insertPoint(pq, makePoint(p.x, p.y-1));
            }

            if (isColorSame(fc, getXY(p.x+1, p.y)) == 1) {
                setXY(1, p.x+1, p.y, C);
                insertPoint(pq, makePoint(p.x+1, p.y));
            }

            if (isColorSame(fc, getXY(p.x, p.y+1)) == 1) {
                setXY(1, p.x, p.y+1, C);
                insertPoint(pq, makePoint(p.x, p.y+1));
            }

            if (isColorSame(fc, getXY(p.x-1, p.y)) == 1) {
                setXY(1, p.x-1, p.y, C);
                insertPoint(pq, makePoint(p.x-1, p.y));
            }
        }
    }
}

