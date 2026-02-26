#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

// função para imprimir o array na tela
void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]); 
    printf("\n"); //quebra de linha no final
}

// função para copiar um array para outro
void copiarArray(int origem[], int destino[], int n) {
    // percorre cada posição
    for(int i = 0; i < n; i++)
        destino[i] = origem[i]; // copia elemento por elemento
}

//BUBBLE SORT
// vai comparando elementos vizinhos e trocando eles de lugar
void bubbleSort(int arr[], int n) {
    // controla quantas passagens serão feitas
    for(int i = 0; i < n - 1; i++) {
        // percorre o array até a parte ainda não ordenada
        for(int j = 0; j < n - i - 1; j++) {
            // se o atual for maior que o próximo, troca
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];      // guarda temporariamente
                arr[j] = arr[j + 1];    // coloca o menor na frente
                arr[j + 1] = temp;      // coloca o maior atrás
            }
        }
    }
}

//SELECTION SORT
//encontra o menor elemento e coloca na posição correta
void selectionSort(int arr[], int n) {
    // percorre cada posição do array
    for(int i = 0; i < n - 1; i++) {
        int min = i; // assume que o menor é o atual

        // procura o menor elemento no restante do array
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[min])
                min = j; // atualiza posição do menor
        }

        // troca o menor encontrado com a posição atual
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

//INSERTION SORT
//pega um elemento e insere na posição correta
void insertionSort(int arr[], int n) {
    // começa do segundo elemento
    for(int i = 1; i < n; i++) {
        int key = arr[i]; // valor atual a ser inserido
        int j = i - 1;

        // move os elementos maiores uma posição à frente
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // coloca o elemento na posição correta
        arr[j + 1] = key;
    }
}

//QUICK SORT
// função que organiza os elementos em torno do pivô
int particiona(int arr[], int low, int high) {
    int pivot = arr[high]; // escolhe o último elemento como pivô
    int i = low - 1;       // índice do menor elemento

    // percorre comparando com o pivô
    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            // troca elemento menor que pivô para esquerda
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // coloca o pivô na posição correta
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1; // retorna posição do pivô
}

// função recursiva do quick sort
void quickSort(int arr[], int low, int high) {
    // verifica se ainda há partes para ordenar
    if(low < high) {
        int pi = particiona(arr, low, high); // divide o array
        quickSort(arr, low, pi - 1);  // ordena lado esquerdo
        quickSort(arr, pi + 1, high); // ordena lado direito
    }
}

//MERGE SORT

// função que junta duas partes já ordenadas
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1; // tamanho da metade esquerda
    int n2 = r - m;     // tamanho da metade direita

    int L[n1], R[n2]; // arrays temporários

    // copia dados para arrays temporários
    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    // junta os dois arrays de forma ordenada
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // copia o que sobrou da esquerda
    while(i < n1) {
        arr[k++] = L[i++];
    }

    // copia o que sobrou da direita
    while(j < n2) {
        arr[k++] = R[j++];
    }
}

// função principal do merge sort
void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = l + (r - l) / 2; // encontra o meio
        mergeSort(arr, l, m);        // ordena metade esquerda
        mergeSort(arr, m + 1, r);    // ordena metade direita
        merge(arr, l, m, r);         // junta as metades
    }
}

//SHELL SORT
// melhora do insertion sort usando intervalos gaps
void shellSort(int arr[], int n) {
    // começa com gap grande e vai diminuindo
    for(int gap = n/2; gap > 0; gap /= 2) {
        for(int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;

            // faz uma espécie de insertion sort com gap
            for(j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}

//fUNÇÃO PRINCIPAL
int main() {
    int tamanho;
    int opcao;

    // pede o tamanho do array
    printf("Digite o tamanho do array: ");
    scanf("%d", &tamanho);

    int original[tamanho]; // array original
    int copia[tamanho];    // array que será ordenado

    srand(time(NULL)); // inicializa semente aleatória

    // preenche array com números aleatórios
    for(int i = 0; i < tamanho; i++) {
        original[i] = rand() % 1000;
    }

    printf("\nArray original:\n");
    printArray(original, tamanho);

    // menu para escolher algoritmo
    printf("\nEscolha um numero para o algoritmo:\n");
    printf("1Bubble Sort\n");
    printf("2Selection Sort\n");
    printf("3Insertion Sort\n");
    printf("4Quick Sort\n");
    printf("5Merge Sort\n");
    printf("6Shell Sort\n");
    scanf("%d", &opcao);

    copiarArray(original, copia, tamanho); // copia antes de ordenar

    clock_t inicio = clock(); 

    switch(opcao) {
        case 1: bubbleSort(copia, tamanho); break;
        case 2: selectionSort(copia, tamanho); break;
        case 3: insertionSort(copia, tamanho); break;
        case 4: quickSort(copia, 0, tamanho - 1); break;
        case 5: mergeSort(copia, 0, tamanho - 1); break;
        case 6: shellSort(copia, tamanho); break;
        default: printf("Nao tem essa opcao\n"); return 1;
    }

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\nArray ordenado:\n");
    printArray(copia, tamanho);

    printf("\nTempo pra executar: %f segundos\n", tempo);

    return 0; 
}