#ifndef COLOR_H
#define COLOR_H

typedef struct {
    int R;
    int G;
    int B;
} Color;

Color setColor(int r, int g, int b);
int isColorSame(Color C1, Color C2);

#endif