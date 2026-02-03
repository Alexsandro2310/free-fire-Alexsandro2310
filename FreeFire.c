#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

/* ================= PROTÓTIPOS ================= */

void cadastrarComponentes(Componente v[], int *n);
void mostrarComponentes(Componente v[], int n);

void bubbleSortNome(Componente v[], int n, long *comparacoes);
void insertionSortTipo(Componente v[], int n, long *comparacoes);
void selectionSortPrioridade(Componente v[], int n, long *comparacoes);

int buscaBinariaPorNome(Componente v[], int n, char chave[], long *comparacoes);

/* ================= FUNÇÕES ================= */

void cadastrarComponentes(Componente v[], int *n) {
    int qtd;
    printf("Quantos componentes deseja cadastrar (max %d)? ", MAX);
    scanf("%d", &qtd);
    getchar();

    if (qtd > MAX) qtd = MAX;

    *n = qtd;

    for (int i = 0; i < qtd; i++) {
        printf("\nComponente %d\n", i + 1);

        printf("Nome: ");
        fgets(v[i].nome, 30, stdin);
        v[i].nome[strcspn(v[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(v[i].tipo, 20, stdin);
        v[i].tipo[strcspn(v[i].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &v[i].prioridade);
        getchar();
    }
}

void mostrarComponentes(Componente v[], int n) {
    printf("\n===== COMPONENTES DA TORRE =====\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

/* -------- Bubble Sort por Nome -------- */
void bubbleSortNome(Componente v[], int n, long *comparacoes) {
    *comparacoes = 0;
    Componente aux;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

/* -------- Insertion Sort por Tipo -------- */
void insertionSortTipo(Componente v[], int n, long *comparacoes) {
    *comparacoes = 0;
    Componente chave;
    int j;

    for (int i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

/* -------- Selection Sort por Prioridade -------- */
void selectionSortPrioridade(Componente v[], int n, long *comparacoes) {
    *comparacoes = 0;
    int min;
    Componente aux;

    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        aux = v[i];
        v[i] = v[min];
        v[min] = aux;
    }
}

/* -------- Busca Binária por Nome -------- */
int buscaBinariaPorNome(Componente v[], int n, char chave[], long *comparacoes) {
    int ini = 0, fim = n - 1, meio;
    *comparacoes = 0;

    while (ini <= fim) {
        meio = (ini + fim) / 2;
        (*comparacoes)++;

        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

/* ================= MAIN ================= */

int main() {
    Componente componentes[MAX];
    int n = 0, opcao;
    long comparacoes;
