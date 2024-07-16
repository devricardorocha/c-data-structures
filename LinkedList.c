#include <stdio.h>
#include <stdbool.h>

// Registro que vai ser o elemento da lista
typedef struct {
    int key;
} Record;

typedef struct {
    Record current;
    LinkedListElement next;
} LinkedListElement;

typedef struct {
    int size = 0;
    LinkedListElement first;
    LinkedListElement last;
} LinkedList;

bool add(LinkedList* list, Record* record) {

    LinkedListElement newLast;
    newLast.current = record;

    if (list->first == NULL)
        list->first = newLast;

    LinkedListElement currentLast = list->last;
    currentLast.next = newLast;

    list->last = newLast;
    list->size++;

    return true;
}

bool hasNext(LinkedListElement* element) {
    return element->next != NULL;
}

void printList(LinkedList* list) {

    LinkedListElement currentEl = list->first;
    while (currentEl != NULL) {

        printf(" %i ", currentEl.current.key);
        currentEl = currentEl.next;

    }

}

int main() {

    LinkedList linkedList;

    Record record1;
    record1.key = 1;
    add(&linkedList, &record1);

    Record record2;
    record2.key = 2;
    add(&linkedList, &record2);

    printList(%linkedList);

    return 0;
}