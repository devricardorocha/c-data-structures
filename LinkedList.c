#include <stdio.h>
#include <stdbool.h>

#define MAX 50
#define INVALID -1

// Registro que vai ser o elemento da lista
typedef struct {
    int key;
} Record;

typedef struct {
    Record record;
    int next;
} LinkedListElement;

typedef struct {
    LinkedListElement a[MAX];
    int first;
    int avaliable;
} LinkedList;

void init(LinkedList* list) {
    int i;
    for (i=0; i < MAX-1; i++)
        list->a[i].next = i + 1;
    list->a[MAX-1].next=INVALID;
    list->first=INVALID;
    list->avaliable=0;
}

int main() {

    LinkedList linkedList;
    init(linkedList);

    return 0;
}