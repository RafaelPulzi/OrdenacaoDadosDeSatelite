#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    float lat;
    float lon;
    float frp;
} DataPoint;

int numComparisons = 0; // Contador para comparações
int numArrayAccesses = 0; // Contador para acessos a arrays

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

void heapify(DataPoint *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Encontrar o maior entre o pai e os filhos
    if (left < n && arr[left].frp > arr[largest].frp) {
        largest = left;
    }
    if (right < n && arr[right].frp > arr[largest].frp) {
        largest = right;
    }

    // Se o maior não for o pai, trocar e chamar heapify recursivamente
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        numComparisons++;
        numArrayAccesses += 4;
        heapify(arr, n, largest);
    }
}

void heapSort(DataPoint *arr, int n) {
    // Construir um max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extrair elementos do heap um por um
    for (int i = n - 1; i > 0; i--) {
        // Mover a raiz atual para o final do array
        swap(&arr[0], &arr[i]);
        numArrayAccesses += 4;
        // Chamar heapify no heap reduzido
        heapify(arr, i, 0);
    }
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
        // Tenta ler os dados usando vírgula como delimitador
        if (sscanf(buffer, "%f,%f,%f", &data[i].lat, &data[i].lon, &data[i].frp) != 3) {
            // Se não foi possível ler usando vírgula, tenta com ponto e vírgula
            sscanf(buffer, "%f;%f;%f", &data[i].lat, &data[i].lon, &data[i].frp);
        }
        i++;
    }

    // Escolha de coluna para ordenação
    int coluna;
    escolhaColuna();
    scanf("%d", &coluna);

    
    clock_t start = clock(); // Marca o tempo de início
    heapSort(data, numLines);
    clock_t end = clock(); // Marca o tempo de término
    // Ordena os dados usando o merge Sort
    
    printf("\n-------------------------------------------------------------\n");
    printf("\nDados apos a ordenacao:\n");
    for (int i = 0; i < numLines; i++) {
        printf("(%.4f, %.4f, %.1f)\n", data[i].lat, data[i].lon, data[i].frp);
    }

    printf("\n-------------------------------------------------------------\n");
    printf("\nNumero de comparacoes feitas: %d\n", numComparisons);
    printf("Numero de acessos a arrays: %d\n", numArrayAccesses);
    double timeSpent = ((double)(end - start)) / CLOCKS_PER_SEC; // Calcula o tempo decorrido em segundos
    printf("Tempo decorrido para ordenacao: %f segundos\n", timeSpent);
    
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
