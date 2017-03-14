#ifndef POINTQUEUE_H
#define POINTQUEUE_H

#include "point.h"

typedef struct qi_t* qi_p;
typedef struct qi_t {
    qi_p next;
    Point data;
} queueItem;
typedef struct {
    queueItem* first;
    queueItem* last;
} queue;
void initQueue(queue* q);
char queueEmpty(queue* q);
void insertPoint(queue* q, Point d);
Point nextPoint(queue* q);


#endif
