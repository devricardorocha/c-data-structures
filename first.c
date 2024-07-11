#include <stdio.h>
#include <malloc.h>
#define alturaMaxina 225

typedef struct{
	int peso;
	int altura;
} PesoAltura;

int main() {
	PesoAltura* pessoa1 = (PesoAltura*) malloc(sizeof(PesoAltura));
	
	pessoa1->peso = 80;
	pessoa1->altura = 170;
	
	printf("Peso: %i, Altura: %i.", pessoa1->peso, pessoa1->altura);

	return 0;
}