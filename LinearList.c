#include <stdio.h>
#define MAX 50

typedef int KeyType;

typedef struct {
    KeyType key;
} Record;

typedef struct 
{
    int size;
    Record a[MAX];
} LinearList;

void init(LinearList* list) {
    list->size = 0;
}

int size(LinearList* list) {
    return list->size;
}

int printList(LinearList* list) {
    printf("List (%i): \" ", list->size);
    for (int i=0;i < list->size - 1; i++)
        printf("%i", list->a[i].key);
    printf("\" \n");
}

int find(LinearList* list, KeyType key) {
    for (int i=0; i < list->size; i++) {
        if (i == list->a[i].key)
            return i;
    }

    return -1;
}

int add(LinearList* list, Record record) {
    int currentSize = list->size;
    list->a[currentSize] = record;
    list->size = currentSize++;
    return currentSize;
}

int main() {

    LinearList list;
    init(&list);

    Record record1;
    record1.key = 1;
    add(&list, record1);

    Record record2;
    record2.key = 2;
    add(&list, record2);

    printList(&list);
    return 0;
}