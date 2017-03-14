#include "pointqueue.h"


//queue
void initQueue(queue* q) {
    q->first = 0;
    q->last = 0;
}

char queueEmpty(queue* q) {
    if ((q->first == 0) ^ (q->last == 0)) {
        printf("WHAT\n");
    }
    return q->first == 0;
}

void insertPoint(queue* q, Point d) {
    queueItem* qi = malloc(sizeof(queueItem));
    qi->data = d;
    qi->next = 0;
    if (queueEmpty(q)) {
        q->first = qi;
    } else {
        q->last->next = qi;
    }
    q->last = qi;
}

Point nextPoint(queue* q) {
    queueItem* qi = q->first;
    q->first = qi->next;
    if (q->first == 0) {
        q->last = 0;
    }
    Point p = qi->data;
    free(qi);
    return p;
}