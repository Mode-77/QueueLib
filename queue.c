/*
    Author: Jared Thomas
    Date:   Tuesday, August 2, 2022
    
    Type-generic queue using singly linked lists
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Node {
    void *          data;
    struct Node *   next;
} Node;

typedef struct Queue {
    Node *  head;
    Node *  tail;
    size_t  data_size;
    size_t  length;
} Queue;

typedef struct Person {
    char const *        name;
    unsigned short int  age;
    char const *        occupation;
} Person;

Queue * create_queue(void);
void    register_new_size(Queue *, size_t data_size);
void    enqueue(Queue *, void *data);
void *  front(Queue *);
size_t  length(Queue *);
void    dequeue(Queue *);
int     is_empty(Queue *);
Queue * copy_queue(Queue *);
void    print(Queue *);
void    destroy_queue(Queue *);



/*
    Creates a heap-allocated node.
    The newly created node has a pointer to 
    a heap-allocated copy of data.
*/
static Node *create_node(void *data, size_t size)
{
    Node *new_node = malloc(sizeof(Node));
    if(new_node == NULL) { return NULL; }
    new_node->data = malloc(size);
    if(new_node->data == NULL) { return NULL; }
    memcpy(new_node->data, data, size);
    new_node->next = NULL;
    return new_node;
}

static void destroy_node(Node *n)
{
    free(n->data);
    free(n);
}

Queue *create_queue(void)
{
    Queue *new_queue = malloc(sizeof(Queue));
    if(new_queue == NULL) { return NULL; }
    new_queue->head = NULL;
    new_queue->tail = NULL;
    new_queue->data_size = 0;
    new_queue->length = 0;
    return new_queue;
}

void register_new_size(Queue *b, size_t data_size)
{
    b->data_size = data_size;
}

/*
    Input data is not null
*/
void enqueue(Queue *b, void *data)
{
    Node *new_node = create_node(data, b->data_size);
    if(new_node == NULL) { assert(0); }

    (b->length)++;

    if(is_empty(b)) {
        b->head = new_node;
        b->tail = new_node;
        return;
    }
    b->tail->next = new_node;
    b->tail = new_node;
}

void *front(Queue *b)
{
    return b->head->data;
}

size_t length(Queue *b)
{
    return b->length;
}

/*
    Input queue is not empty
*/
void dequeue(Queue *b)
{
    if(b->head == b->tail) {
        destroy_node(b->head);
        b->head = NULL;
        b->tail = NULL;
    }
    else {
        Node *upcoming = b->head->next;
        destroy_node(b->head);
        b->head = upcoming;
    }
    (b->length)--;
}

int is_empty(Queue *b)
{
    return b->head == NULL;
}

Queue *copy_queue(Queue *b)
{
    Queue *copy = create_queue();
    copy->data_size = b->data_size;
    int count = length(b);
    while(count > 0) {
        enqueue(copy, front(b));
        dequeue(b);
        enqueue(b, front(copy));
        count--;
    }
    return copy;
}

void print(Queue *b)
{
    if(is_empty(b)) {
        printf("[empty]\n");
        return;
    }
    Queue *copy = copy_queue(b);
    printf("[");
    while(!is_empty(copy)) {
        struct Person *d = (struct Person *)front(copy);
        printf("%s, ", d->name);
        dequeue(copy);
    }
    printf("]");
    printf("\n");
    destroy_queue(copy);
}

void destroy_queue(Queue *b)
{
    while(!is_empty(b)) {
        dequeue(b);
    }
    free(b);
}



int main(void)
{
    Queue *queue = create_queue();
    if(queue == NULL) { assert(0); }
    Person chase = { "Chase", 49, "Banker" };
    Person evan  = { "Evan", 34, "Doctor" };
    Person susie = { "Susie", 43, "Teacher" };
    register_new_size(queue, sizeof(Person));
    enqueue(queue, &chase);
    enqueue(queue, &evan);
    enqueue(queue, &susie);
    print(queue);
    dequeue(queue);
    print(queue);
    dequeue(queue);
    print(queue);
    dequeue(queue);
    print(queue);
    destroy_queue(queue);
    return 0;
}
