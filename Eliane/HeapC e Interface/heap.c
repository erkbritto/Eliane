#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

// Função para gerar valores aleatórios
void GeraValoresAleatorios(int *vetor) {
    for (int i = 1; i <= QTD_ELEM; i++) {
        vetor[i] = rand() % 100;  // Gera números aleatórios entre 0 e 99
    }
}

// Função para imprimir o vetor
void ImprimeVetor(int vetor[]) {
    for (int i = 1; i <= QTD_ELEM; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

// Função Sift para reorganizar o heap
void Sift(int i, int *vetor) {
    int esq = 2 * i;
    int dir = 2 * i + 1;
    int maior = i;

    if (esq <= QTD_ELEM && vetor[esq] > vetor[maior]) {
        maior = esq;
    }
    if (dir <= QTD_ELEM && vetor[dir] > vetor[maior]) {
        maior = dir;
    }
    if (maior != i) {
        int aux = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = aux;
        Sift(maior, vetor);  // Chamando recursivamente para garantir propriedade estrutural
    }
}

// Função Build para transformar o vetor em um heap
void BuildHeap(int *vetor) {
    for (int i = QTD_ELEM / 2; i >= 1; i--) {
        Sift(i, vetor);
    }
}

// Função para determinar os dois maiores elementos
void DeterminaDoisMaioresElementos(int *vetor) {
    if (QTD_ELEM < 2) {
        printf("O vetor deve ter pelo menos dois elementos.\n");
        return;
    }
    int max1 = vetor[1];
    int max2 = vetor[2] > vetor[3] ? vetor[2] : vetor[3];
    printf("Dois maiores elementos: %d e %d\n", max1, max2);
}

int main() {
    int vetor[QTD_ELEM + 1];  // Vetor com 50 elementos, considerando índice 1 como raiz
    
    GeraValoresAleatorios(vetor);
    printf("Vetor original:\n");
    ImprimeVetor(vetor);
    
    BuildHeap(vetor);
    printf("Vetor após BuildHeap:\n");
    ImprimeVetor(vetor);
    
    DeterminaDoisMaioresElementos(vetor);
    
    return 0;
}
