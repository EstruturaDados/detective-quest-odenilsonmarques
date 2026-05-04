#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da sala (nó da árvore)
struct Sala {
    char nome[50];
    char pista[100]; 
    struct Sala* esquerda;
    struct Sala* direita;
};

// Estrutura do nó para pistas
struct NoPista {
    char pista[100];
    struct NoPista* esq;
    struct NoPista* dir;
};

// Criar nova sala
struct Sala* criarSala(const char* nome, const char* pista) {
    struct Sala* nova = malloc(sizeof(struct Sala));

    if (!nova) {
        printf("Erro de memoria!\n");
        exit(1);
    }

    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);

    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

// Criar novo nó de pista
struct NoPista* criarNoPista(const char* pista) {
    struct NoPista* novo = malloc(sizeof(struct NoPista));

    strcpy(novo->pista, pista);
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

// Inserir pista na BST
struct NoPista* inserirPista(struct NoPista* raiz, const char* pista) {
    if (raiz == NULL)
        return criarNoPista(pista);

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirPista(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserirPista(raiz->dir, pista);

    return raiz;
}

// Mostrar pistas em ordem
void mostrarPistas(struct NoPista* raiz) {
    if (raiz != NULL) {
        mostrarPistas(raiz->esq);
        printf("- %s\n", raiz->pista);
        mostrarPistas(raiz->dir);
    }
}

//Exploração da mansão
void explorar(struct Sala* atual, struct NoPista** pistasColetadas) {
    char op;

    while (atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);

        // Coleta pista automaticamente
        if (strlen(atual->pista) > 0) {
            printf("Pista encontrada: %s\n", atual->pista);
            *pistasColetadas = inserirPista(*pistasColetadas, atual->pista);
        }

        printf("\n(e) esquerda | (d) direita | (s) sair\n");
        scanf(" %c", &op);

        if (op == 'e') {
            if (atual->esquerda)
                atual = atual->esquerda;
            else
                printf("Sem caminho à esquerda!\n");
        }
        else if (op == 'd') {
            if (atual->direita)
                atual = atual->direita;
            else
                printf("Sem caminho à direita!\n");
        }
        else if (op == 's') {
            break;
        }
        else {
            printf("Opcao invalida!\n");
        }
    }
}


int main() {

    struct Sala* hall = criarSala("Hall", "");
    struct Sala* sala = criarSala("Sala de Estar", "Pegadas suspeitas");
    struct Sala* cozinha = criarSala("Cozinha", "Faca desaparecida");
    struct Sala* biblioteca = criarSala("Biblioteca", "Livro fora do lugar");
    struct Sala* escritorio = criarSala("Escritorio", "Carta rasgada");
    struct Sala* jardim = criarSala("Jardim", "Pegadas na lama");

    // Montando árvore
    hall->esquerda = sala;
    hall->direita = cozinha;

    sala->esquerda = biblioteca;
    sala->direita = escritorio;

    cozinha->direita = jardim;

    // BST de pistas
    struct NoPista* pistas = NULL;

    printf("=== Detective Quest: Coleta de Pistas ===\n");

    explorar(hall, &pistas);

    // Mostrar resultado final
    printf("\n=== PISTAS COLETADAS (ORDENADAS) ===\n");
    mostrarPistas(pistas);

    return 0;
}