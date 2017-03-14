#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "color.h"
#include "point.h"
#include "grafika.h"


int fbfd;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize;
char *fbp;
int displayWidth, displayHeight;

//basic framebuffer primitive
void initScreen();
void printBackground(Color C);
void setXY (int squareSize, int x, int y, Color C);
Color getXY(int x, int y);
void terminate();


#endif