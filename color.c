#include "color.h"


Color setColor(int r, int g, int b){
    Color X;
    X.R = r;
    X.G = g;
    X.B = b;
    return X;
}

/*
Function untuk mengecek apakah warna C1 == C2
Bisa diatur tingkat kesamaannya pada variable offset
*/
int isColorSame(Color C1, Color C2) {
    int offset = 1;
    if ((abs(C1.R - C2.R) <= offset) && (abs(C1.G - C2.G) <= offset) && (abs(C1.B - C2.B) <= offset)) return 1;
    return 0;
}