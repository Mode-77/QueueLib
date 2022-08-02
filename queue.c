
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct Node {
    char            data;
    struct Node *   next;
} Node;

typedef struct Queue {
    Node *          head;
} Queue;

int is_empty(Queue *);
Queue *create_queue();
void destroy_queue(Queue *);
void enqueue(Queue *, char);
char front(Queue *);
int length(Queue *);
void dequeue(Queue *);
Queue *copy_queue(Queue *);
void print(Queue *);


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

void enqueue(Queue *b, char c)
{
    if(is_empty(b)) {
        b->head = (Node *)malloc(sizeof(Node));
        (b->head)->data = c;
        (b->head)->next = NULL;
        return;
    }
    Node *n = b->head;
    while(n->next != NULL) {
        n = n->next;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = c;
    new_node->next = NULL;
    n->next = new_node;
}

char front(Queue *b)
{
    return (b->head)->data;
}

int length(Queue *b)
{
    Queue *copy = create_queue();
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
    int count = length(b);
    while(count > 0) {
        char d = front(b);
        dequeue(b);
        enqueue(copy, d);
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
    while(!is_empty(copy)) {
        char d = front(copy);
        dequeue(copy);
        printf("%c ", d);
    }
    printf("\n");
    destroy_queue(copy);
}

int main(void)
{
    Queue *queue = create_queue();
    enqueue(queue, 'a');
    enqueue(queue, 'b');
    enqueue(queue, 'c');
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
