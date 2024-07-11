#include <stdio.h>
#include <stdbool.h>
#define MAX 50

typedef int KeyType;

typedef struct {
    KeyType key;
} Record;

typedef struct {
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
    for (int i=0;i < list->size; i++)
        printf("%i ", list->a[i].key);
    printf("\" \n");
}

int find(LinearList* list, KeyType key) {
    for (int i=0; i < list->size; i++) {
        if (key == list->a[i].key)
            return i;
    }

    return -1;
}

bool addToPosition(LinearList* list, Record record, int position) {
    int i;
    if ((list->size == MAX) || (position>list->size))
        return false;

    if (position<0) {
        list->a[list->size] = record;
    } else {
        for (i=list->size; i>position; i--)
            list->a[i] = list->a[i-1];
        
        list->a[i] = record;
    }

    list->size++;
    return true;
}

bool add(LinearList* list, Record record) {
    return addToPosition(list, record, -1);
}

bool delete(KeyType key, LinearList* list) {
    int i, position;
    position = find(list, key);
    if (position<0) return false;
    for (i=position;i<list->size-1;i++)
        list->a[i] = list->a[i+1];
    list->size--;
    return true;
}

int main() {

    LinearList list;
    init(&list);

    Record record1;
    record1.key = 1;
    if (!add(&list, record1)) {
        printf("Failed to add record1\n");
    }

    Record record2;
    record2.key = 2;
    if (!add(&list, record2)) {
        printf("Failed to add record2\n");
    }

    Record record3;
    record3.key = 3;
    if (!addToPosition(&list, record3, 1)) {
        printf("Failed to add record3\n");
    }

    printf("After insertions -> ");
    printList(&list);

    delete(record2.key, &list);
    printf("After deletion -> ");
    printList(&list);

    return 0;
}