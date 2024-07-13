#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX 1000
#define SLEEP 1

// Registro que vai ser o elemento da lista
typedef struct {
    int key;
} Record;

// Implementação de uma lista estática com um tamanho
typedef struct {
    Record a[MAX];
    int size;
} List;

// Inicializar a lista
void init(List* list) {
    list->size = 0;
}

// Adicionar itens à lista ordenando pela chave de forma ascendente
bool addRecordOrderedByKeyAsc(List* list, Record record) {
    int position=0;
    while (position <= list->size-1 && list->a[position].key < record.key)
        position++;

    int i;
    for (i=list->size; i>position; i--)
        list->a[i] = list->a[i-1];
    
    list->a[i] = record;
    list->size++;
    return true;
}

// Algoritmo de busca sequencial/linear -> O(n)
int linearSearch(List* list, int value) {
    for (int i=0; i < list->size; i++) {
        Sleep(SLEEP);
        if (value == list->a[i].key)
            return i;
    }

    return -1;
}

// Algoritmo de busca binária -> O(log n)
int binarySearch(List* list, int value) {
    int left = 0;
    int right = list->size-1;
    int middle;
    while (left <= right) {
        Sleep(SLEEP);
        middle = ((left+right)/2);
        if (list->a[middle].key < value)
            left = middle+1;
        else if (list->a[middle].key > value) 
            right=middle-1;
        else if (left != middle) 
            right=middle-1;
        else
            return middle;
    }
    
    return -1;
}

// Imprimir o resultado do teste no CMD
void printResult(int (*search)(List*, int), List* list, Record record) {

    clock_t start, end; 
    start = clock(); 
    int position = (*search)(list, record.key); 
    end = clock(); 
    double executionTime = ((double) (end - start)) / CLOCKS_PER_SEC;
 
    printf("[value, position, executionTime] = [%i, %i, %f]\n", record.key, position, executionTime); 

}

// Bloco de código que executa o teste (reaproveitável)
void executeTestOverList(int testNumber, List* list) {
    Record record;
    record.key = rand() % MAX;
    printf("Test number %i: \n", testNumber);
    printf("Binary -> ");
    printResult(binarySearch, list, record);
    printf("Sequential -> ");
    printResult(linearSearch, list, record);
    printf("\n");
}

// Carregar itens na lista
bool fillList(List* list) {
    int i=0;
    while (i < MAX) {
        i++;
        Record record;
        record.key = rand() % MAX;
        if (!addRecordOrderedByKeyAsc(list, record)) {
            printf("Failed to add element to list\n");
            return false;
        }
    }

    return true;
}

// Imprima a lista carregada no CMD
void printList(List* list) {
    printf("List (%i): \"[", list->size);
    for (int i=0;i < list->size; i++)
        printf("%i, ", list->a[i].key);
    printf("]\"\n");
}

int main() {

    List list;
    init(&list);

    if (fillList(&list)) {
        printList(&list);
        executeTestOverList(1, &list);
        executeTestOverList(2, &list);
        executeTestOverList(3, &list);
    }

    printf("End of tests");
    return 0;
}