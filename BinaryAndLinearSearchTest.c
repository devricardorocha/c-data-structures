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
        else if (list->a[middle].key > value || (list->a[middle].key == list->a[middle-1].key && left != middle)) 
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

// Carregar itens na lista
bool fillList(List* list, int roof) {
    int i=0;
    while (i < roof) {
        i++;
        Record record;
        record.key = rand() % roof;
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
    for (int i=0;i < list->size-1; i++) {
        printf("%i, ", list->a[i].key);
    }
    printf("%i]\"\n", list->a[list->size-1].key);
}

// Bloco de código que executa o teste (reaproveitável)
void runSearchSpeedTest(int testNumber, Record record, List* list) {
    printf("Test number %i: \n", testNumber);
    printf("Binary -> ");
    printResult(binarySearch, list, record);
    printf("Sequential -> ");
    printResult(linearSearch, list, record);
    printf("\n");
}

// Cria um usuário aleatório e executa o teste
void runRandomRecordSearchSpeedTest(int testNumber, int roof, List* list) {
    Record record;
    record.key = rand() % roof;
    runSearchSpeedTest(testNumber, record, list);
}

// Testes de performance dos algoritmos - INICIO
void runSearchSpeedTestLoop() {

    printf("\nRunning speed tests: \n");

    int roof = 10;
    while (roof <= MAX) {
        List list;
        init(&list);
        printf("\nTest lists with size %i:\n", roof);
        if (fillList(&list, roof)) {
            printList(&list);
            
            Record record;
            record.key = 1;
            runSearchSpeedTest(0, record, &list);
            runRandomRecordSearchSpeedTest(1, roof, &list);
            runRandomRecordSearchSpeedTest(2, roof, &list);
            runRandomRecordSearchSpeedTest(3, roof, &list);
        }

        roof *= 10;
    }
}
// Testes de performance dos algoritmos - FIM

// Testes unitários dos algoritmos - INICIO
bool testListWithSize(int size) {

    List list;
    init(&list);

    for (int i=0; i < size; i++) {
        Record record;
        record.key = i+1;
        addRecordOrderedByKeyAsc(&list, record);
    }

    for (int i=0; i < size; i++) {
        if (binarySearch(&list, i+1) != i) return false;
        if (linearSearch(&list, i+1) != i) return false;
    }

    if (binarySearch(&list, size+1) != -1) return false;
    if (linearSearch(&list, size+1) != -1) return false;

    printf("Passed test with list size %i\n", size);
    return true;
}

bool runSearchValidationTest() {
    
    printf("\nRunning validation tests: \n");

    if(!testListWithSize(0)) return false;
    if(!testListWithSize(1)) return false;
    if(!testListWithSize(2)) return false;
    if(!testListWithSize(3)) return false;

    return true;
}
// Testes unitários dos algoritmos - FIM

int main() {
   
    if (runSearchValidationTest())
        runSearchSpeedTestLoop();
    else 
        printf("Validation test failed\n");

    printf("End of tests\n");
    return 0;
 
}