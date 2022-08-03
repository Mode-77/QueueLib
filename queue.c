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
    size_t  data_size;
    size_t  length;
} Queue;

typedef struct Person {
    char const *        name;
    unsigned short int  age;
    char const *        occupation;
} Person;

Queue * create_queue();
void    register_new_size(Queue *, size_t data_size);
void    enqueue(Queue *, void *data);
void *  front(Queue *);
size_t  length(Queue *);
int     is_empty(Queue *);
void    dequeue(Queue *);
Queue * copy_queue(Queue *);
void    print(Queue *);
void    destroy_queue(Queue *);

int is_empty(Queue *b)
{
    return b->head == NULL;
}

Queue *create_queue()
{
    Queue *new_queue = malloc(sizeof(Queue));
    if(new_queue == NULL) { assert(0); }
    new_queue->head = NULL;
    new_queue->length = 0;
    return new_queue;
}

void destroy_queue(Queue *b)
{
    while(!is_empty(b)) {
        dequeue(b);
    }
    free(b);
}

void enqueue(Queue *b, void *data)
{
    Node *new_node = malloc(sizeof(Node));
    if(new_node == NULL) { assert(0); }
    new_node->data = malloc(b->data_size);
    if(new_node->data == NULL) { assert(0); }
    memcpy(new_node->data, data, b->data_size);
    new_node->next = NULL;

    (b->length)++;

    if(is_empty(b)) {
        b->head = new_node;
        return;
    }
    Node *n = b->head;
    while(n->next != NULL) {
        n = n->next;
    }
    n->next = new_node;
}

void *front(Queue *b)
{
    return (b->head)->data;
}

size_t length(Queue *b)
{
    return b->length;
}

void dequeue(Queue *b)
{
    Node *upcoming = b->head->next;
    free(b->head);
    b->head = NULL;
    if(upcoming != NULL) {
        b->head = upcoming;
    }
    (b->length)--;
}

Queue *copy_queue(Queue *b)
{
    Queue *copy = create_queue();
    register_new_size(copy, b->data_size);
    int count = length(b);
    while(count > 0) {
        void *d = front(b);
        enqueue(copy, d);
        dequeue(b);
        enqueue(b, d);
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

void register_new_size(Queue *b, size_t data_size)
{
    b->data_size = data_size;
}

int main(void)
{
    Queue *queue = create_queue();
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
