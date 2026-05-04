#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

// Estrutura para representar cada sala do mapa
struct Sala {
    char nome[50];
    char pista[100];
    struct Sala* esq;
    struct Sala* dir;
};

// Estrutura para a BST de pistas
struct NoPista {
    char pista[100];
    struct NoPista* esq;
    struct NoPista* dir;
};

// Estrutura para a tabela hash (pista -> suspeito)
struct Hash {
    char pista[100];
    char suspeito[50];
    struct Hash* prox; // encadeamento
};

struct Hash* tabela[TAM_HASH];

// hash para armazenar pistas e suspeitos

// função hash simples
int funcaoHash(const char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++)
        soma += chave[i];
    return soma % TAM_HASH;
}

// inserir na tabela hash
void inserirHash(const char* pista, const char* suspeito) {
    int idx = funcaoHash(pista);

    struct Hash* novo = malloc(sizeof(struct Hash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);

    novo->prox = tabela[idx];
    tabela[idx] = novo;
}

// buscar suspeito pela pista
char* buscarSuspeito(const char* pista) {
    int idx = funcaoHash(pista);

    struct Hash* atual = tabela[idx];
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0)
            return atual->suspeito;
        atual = atual->prox;
    }
    return NULL;
}

// função para criar uma sala
struct Sala* criarSala(const char* nome, const char* pista) {
    struct Sala* s = malloc(sizeof(struct Sala));
    strcpy(s->nome, nome);
    strcpy(s->pista, pista);
    s->esq = s->dir = NULL;
    return s;
}

// inserir pista na BST
struct NoPista* inserirPista(struct NoPista* raiz, const char* pista) {
    if (!raiz) {
        struct NoPista* novo = malloc(sizeof(struct NoPista));
        strcpy(novo->pista, pista);
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirPista(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserirPista(raiz->dir, pista);

    return raiz;
}

// mostrar pistas ordenadas
void mostrarBST(struct NoPista* raiz) {
    if (raiz) {
        mostrarBST(raiz->esq);
        printf("- %s\n", raiz->pista);
        mostrarBST(raiz->dir);
    }
}

// explorar o mapa e coletar pistas
void explorar(struct Sala* atual, struct NoPista** bst, int* cont, char pistasColetadas[][100]) {
    char op;

    while (atual) {
        printf("\nSala: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("Pista: %s\n", atual->pista);

            *bst = inserirPista(*bst, atual->pista);
            strcpy(pistasColetadas[*cont], atual->pista);
            (*cont)++;
        }

        printf("(e) esquerda | (d) direita | (s) sair: ");
        scanf(" %c", &op);

        if (op == 'e') atual = atual->esq;
        else if (op == 'd') atual = atual->dir;
        else break;
    }
}


int main() {

    // inicializar hash
    for (int i = 0; i < TAM_HASH; i++)
        tabela[i] = NULL;

    // mapa
    struct Sala* hall = criarSala("Hall", "");
    struct Sala* sala = criarSala("Sala de Estar", "Pegadas");
    struct Sala* cozinha = criarSala("Cozinha", "Faca");
    struct Sala* biblioteca = criarSala("Biblioteca", "Livro rasgado");
    struct Sala* escritorio = criarSala("Escritorio", "Carta");
    struct Sala* jardim = criarSala("Jardim", "Terra");

    hall->esq = sala;
    hall->dir = cozinha;

    sala->esq = biblioteca;
    sala->dir = escritorio;

    cozinha->dir = jardim;

    // tabela hash (pista -> suspeito)
    inserirHash("Pegadas", "Carlos");
    inserirHash("Faca", "Ana");
    inserirHash("Livro rasgado", "Carlos");
    inserirHash("Carta", "Maria");
    inserirHash("Terra", "Carlos");

    struct NoPista* bst = NULL;

    char pistasColetadas[20][100];
    int total = 0;

    printf("=== Detective Quest FINAL ===\n");

    explorar(hall, &bst, &total, pistasColetadas);

    printf("\n=== PISTAS COLETADAS ===\n");
    mostrarBST(bst);

    // acusação
    char suspeito[50];
    printf("\nQuem é o culpado? ");
    scanf("%s", suspeito);

    int contador = 0;

    for (int i = 0; i < total; i++) {
        char* s = buscarSuspeito(pistasColetadas[i]);

        if (s && strcmp(s, suspeito) == 0)
            contador++;
    }

    if (contador >= 2)
        printf("Acusacao correta! Evidencias suficientes.\n");
    else
        printf("Acusacao fraca! Poucas evidencias.\n");

    return 0;
}