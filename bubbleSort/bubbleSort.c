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

// Função para trocar duas linhas
void swap(DataPoint *a, DataPoint *b) {
    DataPoint temp = *a;
    *a = *b;
    *b = temp;
}

void escolhaDataBase() {
    printf("\n-------------------------------------------------------------");
    printf("\n[1]: Planilha - 500 linhas");
    printf("\n[2]: Planilha - 5000 linhas");
    printf("\n[3]: Planilha - 50000 linhas");
    printf("\n[4]: Planilha - 250000 linhas");
    printf("\n[5]: Planilha - 1000000 linhas");
    printf("\n-------------------------------------------------------------");
    printf("\nEscolha qual base de dados deseja fazer a ordenacao?\n");
}

void escolhaColuna() {
    printf("\n-------------------------------------------------------------\n");
    printf("\n[1]: Para a coluna lat.\n");
    printf("[2]: Para a coluna lon.\n");
    printf("[3]: Para a coluna frp.\n");
    printf("\n-------------------------------------------------------------\n");
    printf("\nEm qual coluna deseja fazer a ordenacao?\n");
}

// Função para realizar a ordenação usando Bubble Sort e capturar o número de iterações
int bubbleSort(DataPoint *arr, int n, int coluna) {
    int iterations = 0; // Inicialize o contador de iterações

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            iterations++; // Incrementar o contador em cada iteração

            switch (coluna) {
                case 1:
                    if (arr[j].lat > arr[j + 1].lat) {
                        swap(&arr[j], &arr[j + 1]);
                    }
                    break;
                case 2:
                    if (arr[j].lon > arr[j + 1].lon) {
                        swap(&arr[j], &arr[j + 1]);
                    }
                    break;
                case 3:
                    if (arr[j].frp > arr[j + 1].frp) {
                        swap(&arr[j], &arr[j + 1]);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    return iterations; // Retornar o número total de iterações
}

int main() {
    int database;
    escolhaDataBase();
    scanf("%d", &database);

    const char *filenames[] = {
        "C:\\Users\\Pulzi\\Desktop\\Projetos\\Aps4Semestre\\0dados\\planilha - 500 linhas.csv",
        "C:\\Users\\Pulzi\\Desktop\\Projetos\\Aps4Semestre\\0dados\\planilha - 5000 linhas.csv",
        "C:\\Users\\Pulzi\\Desktop\\Projetos\\Aps4Semestre\\0dados\\planilha - 50000 linhas.csv",
        "C:\\Users\\Pulzi\\Desktop\\Projetos\\Aps4Semestre\\0dados\\planilha - 250000 linhas.csv",
        "C:\\Users\\Pulzi\\Desktop\\Projetos\\Aps4Semestre\\0dados\\planilha - 1000000 linhas.csv"
    };

    if (database < 1 || database > 5) {
        printf("Opção de base de dados inválida.\n");
        return 1;
    }

    FILE *file = fopen(filenames[database - 1], "r");
    
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
        fprintf(stderr, "Erro de alocacao de memoria.\n");
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
    printf("\n-------------------------------------------------------------\n");
    printf("Dados antes da ordenacao:\n");
    for (int i = 0; i < numLines; i++) {
        printf("(%.4f, %.4f, %.1f)\n", data[i].lat, data[i].lon, data[i].frp);
    }
    // Escolha de coluna para ordenação
    int coluna;
    escolhaColuna();
    scanf("%d", &coluna);
    // Ordena os dados usando o Bubble Sort
    int numIterations = bubbleSort(data, numLines, coluna);
    printf("\n-------------------------------------------------------------\n");
    printf("\nDados apos a ordenacao:\n");
    for (int i = 0; i < numLines; i++) {
        printf("(%.4f, %.4f, %.1f)\n", data[i].lat, data[i].lon, data[i].frp);
    }
    printf("\n-------------------------------------------------------------\n");
    printf("\nNumero de iteracoes: %d\n", numIterations);
    
    switch (coluna) {
        case 1:
            printf("Ordenado pela coluna lat.");
            break;
        case 2:
            printf("Ordenado pela coluna lon.");
            break;
        case 3:
            printf("Ordenado pela coluna frp.");
            break;
        default:
            break;
    }

    free(data); // Liberar a memória alocada
    
    return 0;
}
