#ifndef DXQUEUE_H
#define DXQUEUE_H

typedef struct Queue Queue;

Queue * create_queue(void);
void    enqueue(Queue *, void *data, size_t data_size);
void *  front(Queue *);
size_t  front_size(Queue const *);
size_t  length(Queue const *);
void    dequeue(Queue *);
void    clear(Queue *);
int     is_empty(Queue const *);
Queue * copy_queue(Queue const *);
void    print(Queue *);
void    destroy_queue(Queue *);

#endif
