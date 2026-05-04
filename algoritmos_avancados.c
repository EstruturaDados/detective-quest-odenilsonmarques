#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Estrutura da sala

Cada sala possui:
- nome: identificação do cômodo
- esquerda: caminho à esquerda
- direita: caminho à direita
*/
struct Sala
{
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
};

// Cria uma nova sala (nó da árvore) com nome e sem filhos.
struct Sala *criarSala(const char *nome)
{
    struct Sala *nova = (struct Sala *)malloc(sizeof(struct Sala));

    if (nova == NULL)
    {
        printf("Erro de memoria!\n");
        exit(1);
    }

    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
}

/*
Função para explorar a mansão (navegar pela árvore)

Permite ao jogador navegar pela árvore:

- 'e' -> esquerda
- 'd' -> direita

A exploração continua até chegar em um nó folha.
*/
void explorarMansao(struct Sala *atual)
{
    char opcao;

    while (atual != NULL)
    {
        printf("\nVoce esta em: %s\n", atual->nome);

        // Se for folha → fim do jogo
        if (atual->esquerda == NULL && atual->direita == NULL)
        {
            printf("Fim do caminho! Investigacao encerrada.\n");
            break;
        }

        printf("Escolha o caminho (e = esquerda, d = direita): ");
        scanf(" %c", &opcao);

        if (opcao == 'e')
        {
            if (atual->esquerda != NULL)
                atual = atual->esquerda;
            else
                printf("Nao ha caminho à esquerda!\n");
        }
        else if (opcao == 'd')
        {
            if (atual->direita != NULL)
                atual = atual->direita;
            else
                printf("Nao ha caminho à direita!\n");
        }
        else
        {
            printf("Opcao invalida!\n");
        }
    }
}

int main()
{

    struct Sala *hall = criarSala("Hall");
    struct Sala *salaEstar = criarSala("Sala de Estar");
    struct Sala *cozinha = criarSala("Cozinha");
    struct Sala *biblioteca = criarSala("Biblioteca");
    struct Sala *escritorio = criarSala("Escritorio");
    struct Sala *jardim = criarSala("Jardim");

    // Ligando as salas (montando a árvore)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = escritorio;

    cozinha->direita = jardim;

    // Início do jogo
    printf("=== Detective Quest ===\n");
    printf("Explore a mansao e encontre pistas...\n");

    explorarMansao(hall);

    return 0;
}