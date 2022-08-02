
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct Person {
    char const *        name;
    unsigned short int  age;
    char const *        occupation;
};

typedef struct Node {
    void *          data;
    struct Node *   next;
} Node;

typedef struct Queue {
    Node *  head;
    size_t  data_size;
} Queue;

int is_empty(Queue *);
Queue *create_queue();
void destroy_queue(Queue *);
void enqueue(Queue *, void *data);
void *front(Queue *);
int length(Queue *);
void dequeue(Queue *);
Queue *copy_queue(Queue *);
void print(Queue *);
void register_new_size(Queue *, size_t data_size);

int is_empty(Queue *b)
{
    if(b->head == NULL) { return 1; }
    return 0;
}

Queue *create_queue()
{
    Queue *new_queue = (Queue *)malloc(sizeof(Queue));
    new_queue->head = NULL;
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
    if(is_empty(b)) {
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->data = malloc(b->data_size);
        memcpy(new_node->data, data, b->data_size);
        new_node->next = NULL;
        b->head = new_node;
        return;
    }
    Node *n = b->head;
    while(n->next != NULL) {
        n = n->next;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = malloc(b->data_size);
    memcpy(new_node->data, data, b->data_size);
    new_node->next = NULL;
    n->next = new_node;
}

void *front(Queue *b)
{
    return (b->head)->data;
}

int length(Queue *b)
{
    Queue *copy = create_queue();
    register_new_size(copy, b->data_size);
    int count = 0;
    while(!is_empty(b)) {
        enqueue(copy, front(b));
        dequeue(b);
        count++;
    }
    while(!is_empty(copy)) {
        enqueue(b, front(copy));
        dequeue(copy);
    }
    destroy_queue(copy);
    return count;
}

void dequeue(Queue *b)
{
    Node *upcoming = b->head->next;
    free(b->head);
    b->head = NULL;
    if(upcoming != NULL) {
        b->head = upcoming;
    }
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
    struct Person chase = { "Chase", 49, "Banker" };
    struct Person evan  = { "Evan", 34, "Doctor" };
    struct Person susie = { "Susie", 43, "Teacher" };
    register_new_size(queue, sizeof(struct Person));
    enqueue(queue, &chase);
    enqueue(queue, &evan);
    enqueue(queue, &susie);
    printf("length: %d\n", length(queue));
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
