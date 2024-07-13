#include <stdio.h>
#include <stdbool.h>
#define MAX 50

typedef int KeyType;

typedef struct {
    KeyType key;
} Record;

typedef struct {
    int size;
    Record a[MAX+1];
} OptimizedLinearList;

void init(OptimizedLinearList* list) {
    list->size = 0;
}

int size(OptimizedLinearList* list) {
    return list->size;
}

int printList(OptimizedLinearList* list) {
    printf("List (%i): \" ", list->size);
    for (int i=0;i < list->size; i++)
        printf("%i ", list->a[i].key);
    printf("\" \n");
}

int find(OptimizedLinearList* list, KeyType key) {
    int i=0;
    list->a[list->size].key = key;
    while (list->a[i].key != key) i++;
    if (i == list->size) return -1;
    else return i;
}

int findUsingBinarySearch(OptimizedLinearList* list, KeyType key) {
    int left = 0;
    int right = list->size-1;
    int middle;
    while (left <= right) {
        middle = ((left+right)/2);
        if (list->a[middle].key < key)
            left = middle+1;
        else if (list->a[middle].key > key) 
            right=middle-1;
        else
            return middle;
    }
    
    return -1;
}

bool addToPosition(OptimizedLinearList* list, Record record, int position) {
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

bool add(OptimizedLinearList* list, Record record) {
    int i=0;
    while (i <= list->size-1 && list->a[i].key < record.key) i++;
    return addToPosition(list, record, i);
}

bool delete(KeyType key, OptimizedLinearList* list) {
    int i, position;
    position = find(list, key);
    if (position<0) return false;
    for (i=position;i<list->size-1;i++)
        list->a[i] = list->a[i+1];
    list->size--;
    return true;
}

void logErrorForField(char field[]) {
    printf("Failed to add %s\n", field);
}

int main() {

    OptimizedLinearList list;
    init(&list);

    Record record7;
    record7.key = 7;
    if (!add(&list, record7))
        logErrorForField("record7");

    Record record2;
    record2.key = 2;
    if (!add(&list, record2))
        logErrorForField("record2");

    Record record3;
    record3.key = 3;
    if (!addToPosition(&list, record3, 1))
        logErrorForField("record3");

    Record record12;
    record12.key = 12;
    if (!add(&list, record12))
        logErrorForField("record12");
    
    Record record4;
    record4.key = 4;
    if (!add(&list, record4))
        logErrorForField("record4");
    
    Record record6;
    record6.key = 1;
    if (!add(&list, record6))
        logErrorForField("record6");

    printf("After insertions -> ");
    printList(&list);

    delete(record2.key, &list);
    printf("After deletion -> ");
    printList(&list);

    int r7 = find(&list, record7.key);
    printf("Position of record7: %i\n", r7);

    int r4 = findUsingBinarySearch(&list, record7.key);
    printf("Position of record7: %i\n", r4);
 
    return 0;
}