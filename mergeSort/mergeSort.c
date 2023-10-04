#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float lat;
    float lon;
    float frp;
} DataPoint;

// Variáveis globais para contar comparações e acessos ao array
int comparisons = 0;
int arrayAccesses = 0;

void merge(DataPoint arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    DataPoint L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {

        // Incrementa o contador de comparações
        comparisons++;

        if (L[i].frp <= R[j].frp) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        // Incrementa o contador de acessos ao array
        arrayAccesses++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(DataPoint arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
    FILE *file = fopen("C:\\Users\\Pulzi\\Desktop\\Projetos\\Aps4Semestre\\mergeSort\\planilha - 500 linhas.csv", "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Contando o número de linhas no arquivo para alocar memória
    int numLines = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        numLines++;
    }
    rewind(file);

    // Alocando memória para armazenar os dados
    DataPoint *data = malloc(numLines * sizeof(DataPoint));
    if (data == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        fclose(file);
        return 1;
    }

    // Lendo os dados do arquivo CSV e armazenando na estrutura DataPoint
    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        sscanf(buffer, "%f,%f,%f", &data[i].lat, &data[i].lon, &data[i].frp);
        i++;
    }

    fclose(file);

    printf("Dados antes da ordenação:\n");
    for (int i = 0; i < numLines; i++) {
        printf("(%.4f, %.4f, %.1f)\n", data[i].lat, data[i].lon, data[i].frp);
    }

    mergeSort(data, 0, numLines - 1);

    printf("\nDados após a ordenação por FRP:\n");
    for (int i = 0; i < numLines; i++) {
        printf("(%.4f, %.4f, %.1f)\n", data[i].lat, data[i].lon, data[i].frp);
    }

    // Imprime o número de comparações e acessos ao array
    printf("\nNúmero de comparações: %d\n", comparisons);
    printf("Número de acessos ao array: %d\n", arrayAccesses);

    // Liberando a memória alocada
    free(data);

    return 0;
}
