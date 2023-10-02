#include <stdio.h>

struct Contadores {
    int comparacoes; // Número de comparações entre elementos durante a ordenação
    int acessos_array; // Número de acessos a elementos do array durante a ordenação
};

void merge(int arr[], int esquerda, int meio, int direita, struct Contadores *contadores) {
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    int ArrayEsquerdo[n1], ArrayDireito[n2];

    for (i = 0; i < n1; i++) {
        ArrayEsquerdo[i] = arr[esquerda + i];
        contadores->acessos_array++;
    }
    for (j = 0; j < n2; j++) {
        ArrayDireito[j] = arr[meio + 1 + j];
        contadores->acessos_array++;
    }

    i = 0;
    j = 0;
    k = esquerda;
    while (i < n1 && j < n2) {
        contadores->comparacoes++;
        if (ArrayEsquerdo[i] <= ArrayDireito[j]) {
            arr[k] = ArrayEsquerdo[i];
            i++;
        } else {
            arr[k] = ArrayDireito[j];
            j++;
        }
        contadores->acessos_array++;
        k++;
    }

    while (i < n1) {
        arr[k] = ArrayEsquerdo[i];
        i++;
        k++;
        contadores->acessos_array++;
    }

    while (j < n2) {
        arr[k] = ArrayDireito[j];
        j++;
        k++;
        contadores->acessos_array++;
    }
}

void mergeSort(int arr[], int esquerda, int direita, struct Contadores *contadores) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSort(arr, esquerda, meio, contadores);
        mergeSort(arr, meio + 1, direita, contadores);
        merge(arr, esquerda, meio, direita, contadores);
    }
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int tamanho_arr = sizeof(arr) / sizeof(arr[0]);
    struct Contadores contadores = {0, 0};

    mergeSort(arr, 0, tamanho_arr - 1, &contadores);

    printf("Array ordenado: ");
    for (int i = 0; i < tamanho_arr; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Comparações: %d\n", contadores.comparacoes);
    printf("Acessos ao array: %d\n", contadores.acessos_array);

    return 0;
}

