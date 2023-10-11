#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    float lat;
    float lon;
    float frp;
} DataPoint;

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

void swap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

int partition(DataPoint arr[], int low, int high, int coluna) {
    float pivot;
    
    if(coluna == 1)
        pivot = arr[high].lat;
    else if(coluna == 2)
        pivot = arr[high].lon;
    else
        pivot = arr[high].frp;

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        float valorComparado;

        if(coluna == 1)
            valorComparado = arr[j].lat;
        else if(coluna == 2)
            valorComparado = arr[j].lon;
        else
            valorComparado = arr[j].frp;

        if (valorComparado < pivot) {
            i++;
            swap(&arr[i].lat, &arr[j].lat);
            swap(&arr[i].lon, &arr[j].lon);
            swap(&arr[i].frp, &arr[j].frp);
        }
    }
    
    swap(&arr[i + 1].lat, &arr[high].lat);
    swap(&arr[i + 1].lon, &arr[high].lon);
    swap(&arr[i + 1].frp, &arr[high].frp);

    return (i + 1);
}

void quickSort(DataPoint arr[], int low, int high, int coluna) {
    if (low < high) {
        int pi = partition(arr, low, high, coluna);
        quickSort(arr, low, pi - 1, coluna);
        quickSort(arr, pi + 1, high, coluna);
    }
}


int main() {
	int database;
	escolhaDataBase();
	scanf("%d", &database);

	const char *filenames[] = {
		//"C:\\Users\\Henrique\\Desktop\\Faculdade\\GitHub\\Aps4Semestre\\bubbleSort\\dados\\planilha - 500 linhas.csv",
        //"C:\\Users\\Henrique\\Desktop\\Faculdade\\GitHub\\Aps4Semestre\\bubbleSort\\dados\\planilha - 5000 linhas.csv",
        //"C:\\Users\\Henrique\\Desktop\\Faculdade\\GitHub\\Aps4Semestre\\bubbleSort\\dados\\planilha - 50000 linhas.csv",
        //"C:\\Users\\Henrique\\Desktop\\Faculdade\\GitHub\\Aps4Semestre\\bubbleSort\\dados\\planilha - 250000 linhas.csv",
        //"C:\\Users\\Henrique\\Desktop\\Faculdade\\GitHub\\Aps4Semestre\\bubbleSort\\dados\\planilha - 1000000 linhas.csv"
		"C:\\Users\\Unip\\Desktop\\arquivos csv\\planilha - 500 linhas.csv"
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

	int numLines = 0;
	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		numLines++;
	}
	rewind(file);

	DataPoint *data = malloc(numLines * sizeof(DataPoint));
	if (data == NULL) {
		fprintf(stderr, "Erro de alocacao de memoria.\n");
		fclose(file);
		return 1;
	}

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
	
	int coluna;
	escolhaColuna();
	scanf("%d", &coluna);

	if(coluna < 1 || coluna > 3){
		printf("Opção de coluna inválida.\n");
		return 1;
	}

	quickSort(data, 0, numLines - 1, coluna);

	printf("\n-------------------------------------------------------------\n");
	printf("Dados após a ordenacao:\n");
	for (int i = 0; i < numLines; i++) {
		printf("(%.4f, %.4f, %.1f)\n", data[i].lat, data[i].lon, data[i].frp);
	}

	free(data);

	return 0;
}