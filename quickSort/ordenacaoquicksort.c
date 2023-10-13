#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    float lat;
    float lon;
    float frp;
} DataPoint;

int interactions = 0;

int compare(const void *a, const void *b, int column) {
    DataPoint *dataA = (DataPoint *)a;
    DataPoint *dataB = (DataPoint *)b;

    switch (column) {
        case 1:
            if (dataA->lat < dataB->lat) return -1;
            if (dataA->lat > dataB->lat) return 1;
            break;
        case 2:
            if (dataA->lon < dataB->lon) return -1;
            if (dataA->lon > dataB->lon) return 1;
            break;
        case 3:
            if (dataA->frp < dataB->frp) return -1;
            if (dataA->frp > dataB->frp) return 1;
            break;
        default:
            return 0;
    }

    return 0;
}

void swap(DataPoint *a, DataPoint *b) {
    DataPoint temp = *a;
    *a = *b;
    *b = temp;
}

int partition(DataPoint arr[], int low, int high, int column) {
    float pivot;
    if (column == 1) {
        pivot = arr[high].lat;
    } else if (column == 2) {
        pivot = arr[high].lon;
    } else if (column == 3) {
        pivot = arr[high].frp;
    } else {
        return -1; // Coluna inválida
    }

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (compare(&arr[j], &arr[high], column) < 0) {
            i++;
            swap(&arr[i], &arr[j]);
            interactions++;
        }
    }

    swap(&arr[i + 1], &arr[high]);
    interactions++;

    return (i + 1);
}

void quickSort(DataPoint arr[], int low, int high, int column) {
    if (low < high) {
        int pi = partition(arr, low, high, column);
        quickSort(arr, low, pi - 1, column);
        quickSort(arr, pi + 1, high, column);
    }
}

int main() {
    int database, column;
    printf("\n-------------------------------------------------------------");
    printf("\n[1]: Planilha - 500 linhas");
    printf("\n[2]: Planilha - 5000 linhas");
    printf("\n[3]: Planilha - 50000 linhas");
    printf("\n[4]: Planilha - 250000 linhas");
    printf("\n[5]: Planilha - 1000000 linhas");
    printf("\n-------------------------------------------------------------");
    printf("\nEscolha qual base de dados deseja fazer a ordenacao?\n");
    scanf("%d", &database);
    printf("Escolha qual coluna deseja ordenar? (1 - lat, 2 - lon, 3 - frp)\n");
    scanf("%d", &column);

    if (database < 1 || database > 5) {
        printf("Opção de base de dados inválida.\n");
        return 1;
    }

    if (column < 1 || column > 3) {
        printf("Opção de coluna inválida.\n");
        return 1;
    }

    const char *filenames[] = {
        "C:\\Users\\joaov\\Documents\\arquivos csv\\planilha - 500 linhas.csv",
        "C:\\Users\\joaov\\Documents\\arquivos csv\\planilha - 5000 linhas.csv",
        "C:\\Users\\joaov\\Documents\\arquivos csv\\planilha - 50000 linhas.csv",
        "C:\\Users\\joaov\\Documents\\arquivos csv\\planilha - 250000 linhas.csv",
        "C:\\Users\\joaov\\Documents\\arquivos csv\\planilha - 1000000 linhas.csv"
    };

    FILE *file = fopen(filenames[database - 1], "r");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    int numLines = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        numLines++;
    }
    rewind(file);

    DataPoint *data = malloc(numLines * sizeof(DataPoint));
    if (data == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        fclose(file);
        return 1;
    }

    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (sscanf(buffer, "%f,%f,%f", &data[i].lat, &data[i].lon, &data[i].frp) != 3) {
            sscanf(buffer, "%f;%f;%f", &data[i].lat, &data[i].lon, &data[i].frp);
        }
        i++;
    }

    fclose(file);

    printf("\n-------------------------------------------------------------\n");
    printf("Dados antes da ordenacao:\n");
    for (int i = 0; i < numLines; i++) {
        printf("(%.4f, %.4f, %.1f)\n", data[i].lat, data[i].lon, data[i].frp);
    }

    interactions = 0;

    clock_t start_time = clock();

    quickSort(data, 0, numLines - 1, column);

    clock_t end_time = clock();

    double total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\n-------------------------------------------------------------\n");
    printf("Dados após a ordenacao:\n");
    for (int i = 0; i < numLines; i++) {
        printf("(%.4f, %.4f, %.1f)\n", data[i].lat, data[i].lon, data[i].frp);
    }

    printf("Tempo de ordenação: %.4f segundos\n", total_time);

    printf("\nNúmero de interações: %d\n", interactions);

    free(data);

    return 0;
}