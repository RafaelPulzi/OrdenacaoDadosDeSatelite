#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
unsigned long long int bubbleSort(DataPoint *arr, int n, int coluna) {
    unsigned long long int iterations = 0; // Inicialize o contador de iterações

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
    char choice[256]; // Variável para a escolha do usuário

    while (1) { // Loop infinito
        int database;
        escolhaDataBase();
        scanf("%d", &database);

        // Defina os nomes de arquivo e outros detalhes aqui
        const char *filenames[] = {
            "C:\\Users\\Henrique\\Desktop\\Faculdade\\GitHub\\Aps4Semestre\\0dados\\planilha - 500 linhas.csv",
            "C:\\Users\\Henrique\\Desktop\\Faculdade\\GitHub\\Aps4Semestre\\0dados\\planilha - 5000 linhas.csv",
            "C:\\Users\\Henrique\\Desktop\\Faculdade\\GitHub\\Aps4Semestre\\0dados\\planilha - 50000 linhas.csv",
            "C:\\Users\\Henrique\\Desktop\\Faculdade\\GitHub\\Aps4Semestre\\0dados\\planilha - 250000 linhas.csv",
            "C:\\Users\\Henrique\\Desktop\\Faculdade\\GitHub\\Aps4Semestre\\0dados\\planilha - 1000000 linhas.csv"
        };

        if (database < 1 || database > 5) {
            printf("Opção de base de dados inválida.\n");
            continue; // Retorna ao início do loop
        }

        FILE *file = fopen(filenames[database - 1], "r");

        if (file == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo.\n");
            continue; // Retorna ao início do loop
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
        printf("Dados Carregados com sucesso\n");

        // Escolha de coluna para ordenação
        int coluna;
        escolhaColuna();
        scanf("%d", &coluna);

        clock_t start_time, end_time; // Variáveis para medir o tempo
        printf("Algoritmo de ordenacao em execucao, aguarde...\n");
        // Iniciar a contagem de tempo antes de chamar o bubbleSort
        start_time = clock();

        // Ordena os dados usando o Bubble Sort
        unsigned long long int numIterations = bubbleSort(data, numLines, coluna);

        // Finaliza a contagem de tempo após o bubbleSort
        end_time = clock();

        printf("\nDados ordenados com sucesso\n");
        printf("Numero de iteracoes: %llu\n", numIterations);

        double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Tempo gasto na ordenacao: %.6f segundos\n", elapsed_time);

        // Libera a memória alocada
        free(data);

        // Pergunta ao usuário se deseja encerrar
        printf("\nDeseja fechar o programa? Se sim, pressione Enter. Caso contrário, insira qualquer texto e pressione Enter.\n");
        scanf("%s", choice);

        if (strlen(choice) == 0) { // Se a entrada for uma linha vazia (somente Enter), encerre o programa
            break; // Sai do loop
        }
    }

    return 0;
}
