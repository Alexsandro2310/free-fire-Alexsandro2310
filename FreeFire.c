#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ================= STRUCTS =================

// Item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ================= CONTADORES =================
int compSeqVetor = 0;
int compBinVetor = 0;
int compLista = 0;

// ================= FUNÇÕES VETOR =================

void inserirItemVetor(Item v[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("Nome: ");
    fgets(v[*total].nome, 30, stdin);
    v[*total].nome[strcspn(v[*total].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(v[*total].tipo, 20, stdin);
    v[*total].tipo[strcspn(v[*total].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &v[*total].quantidade);
    getchar();

    (*total)++;
}

void listarVetor(Item v[], int total) {
    if (total == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("[%d] %s | %s | %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].quantidade);
    }
}

void removerItemVetor(Item v[], int *total, char nome[]) {
    for (int i = 0; i < *total; i++) {
        if (strcmp(v[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++) {
                v[j] = v[j + 1];
            }
            (*total)--;
            printf("Item removido.\n");
            return;
        }
    }
    printf("Item não encontrado.\n");
}

int buscarSequencialVetor(Item v[], int total, char nome[]) {
    compSeqVetor = 0;
    for (int i = 0; i < total; i++) {
        compSeqVetor++;
        if (strcmp(v[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

void ordenarVetor(Item v[], int total) {
    Item aux;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

int buscarBinariaVetor(Item v[], int total, char nome[]) {
    int ini = 0, fim = total - 1;
    compBinVetor = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        compBinVetor++;

        int cmp = strcmp(nome, v[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            ini = meio + 1;
    }
    return -1;
}

// ================= FUNÇÕES LISTA =================

No* inserirItemLista(No* inicio, Item item) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dados = item;
    novo->proximo = inicio;
    return novo;
}

void listarLista(No* inicio) {
    if (!inicio) {
        printf("Mochila vazia.\n");
        return;
    }

    int i = 1;
    while (inicio) {
        printf("[%d] %s | %s | %d\n",
               i++, inicio->dados.nome,
               inicio->dados.tipo,
               inicio->dados.quantidade);
        inicio = inicio->proximo;
    }
}

No* buscarLista(No* inicio, char nome[]) {
    compLista = 0;
    while (inicio) {
        compLista++;
        if (strcmp(inicio->dados.nome, nome) == 0)
            return inicio;
        inicio = inicio->proximo;
    }
    return NULL;
}

No* removerItemLista(No* inicio, char nome[]) {
    No *ant = NULL, *atual = inicio;

    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (ant == NULL)
                inicio = atual->proximo;
            else
                ant->proximo = atual->proximo;

            free(atual);
            printf("Item removido.\n");
            return inicio;
        }
        ant = atual;
        atual = atual->proximo;
    }

    printf("Item não encontrado.\n");
    return inicio;
}

// ================= MAIN =================

int main() {
    Item vetor[MAX_ITENS];
    int total = 0;

    No* lista = NULL;

    int estrutura, opcao;
    char nomeBusca[30];

    printf("Escolha a estrutura:\n");
    printf("1 - Vetor\n");
    printf("2 - Lista Encadeada\n");
    scanf("%d", &estrutura);
    getchar();

    do {
        printf("\n1 Inserir\n2 Remover\n3 Listar\n4 Buscar\n5 Ordenar (vetor)\n6 Busca Binaria (vetor)\n0 Sair\n");
        scanf("%d", &opcao);
        getchar();

        if (estrutura == 1) { // VETOR
            switch (opcao) {
                case 1:
                    inserirItemVetor(vetor, &total);
                    break;
                case 2:
                    printf("Nome: ");
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    removerItemVetor(vetor, &total, nomeBusca);
                    break;
                case 3:
                    listarVetor(vetor, total);
                    break;
                case 4: {
                    printf("Nome: ");
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    int pos = buscarSequencialVetor(vetor, total, nomeBusca);
                    if (pos >= 0)
                        printf("Encontrado com %d comparações.\n", compSeqVetor);
                    else
                        printf("Não encontrado (%d comparações).\n", compSeqVetor);
                    break;
                }
                case 5:
                    ordenarVetor(vetor, total);
                    printf("Vetor ordenado.\n");
                    break;
                case 6: {
                    printf("Nome: ");
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    int pos = buscarBinariaVetor(vetor, total, nomeBusca);
                    if (pos >= 0)
                        printf("Encontrado com %d comparações.\n", compBinVetor);
                    else
                        printf("Não encontrado (%d comparações).\n", compBinVetor);
                    break;
                }
            }
        } else { // LISTA
            Item temp;
            switch (opcao) {
                case 1:
                    printf("Nome: ");
                    fgets(temp.nome, 30, stdin);
                    temp.nome[strcspn(temp.nome, "\n")] = '\0';
                    printf("Tipo: ");
                    fgets(temp.tipo, 20, stdin);
                    temp.tipo[strcspn(temp.tipo, "\n")] = '\0';
                    printf("Quantidade: ");
                    scanf("%d", &temp.quantidade);
                    getchar();
                    lista = inserirItemLista(lista, temp);
                    break;
                case 2:
                    printf("Nome: ");
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    lista = removerItemLista(lista, nomeBusca);
                    break;
                case 3:
                    listarLista(lista);
                    break;
                case 4: {
                    printf("Nome: ");
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    No* r = buscarLista(lista, nomeBusca);
                    if (r)
                        printf("Encontrado com %d comparações.\n", compLista);
                    else
                        printf("Não encontrado (%d comparações).\n", compLista);
                    break;
                }
            }
        }

    } while (opcao != 0);

    return 0;
}
