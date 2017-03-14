#ifndef KEYPRESS_H
#define KEYPRESS_H

#include <termios.h>
#include <unistd.h>

#define ENTER_KEYPRESS 10
#define LEFT_KEYPRESS 68
#define RIGHT_KEYPRESS 67
#define UP_KEYPRESS 66
#define DOWN_KEYPRESS 65
#define ZOOMIN_KEYPRESS 61
#define ZOOMOUT_KEYPRESS 45
#define TOGGLE_BUILDING_KEYPRESS 122
#define TOGGLE_ROADS_KEYPRESS 120
#define TOGGLE_TREES_KEYPRESS 99
#define ROTATE_KEYPRESS 114
int getch(void);


#endif