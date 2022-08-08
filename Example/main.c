#include <stdlib.h>
#include <assert.h>

#include "..\DXQueue\dxqueue.h"

typedef struct Person {
    char const *        name;
    unsigned short int  age;
    char const *        occupation;
} Person;

int main(void)
{
    Queue *queue = create_queue();
    if(queue == NULL) { assert(0); }
    Person chase = { "Chase", 49, "Banker" };
    Person evan  = { "Evan", 34, "Doctor" };
    Person susie = { "Susie", 43, "Teacher" };
    enqueue(queue, &chase, sizeof(Person));
    enqueue(queue, &evan, sizeof(Person));
    enqueue(queue, &susie, sizeof(Person));
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
