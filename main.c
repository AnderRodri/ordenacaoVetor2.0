#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura da lista encadeada
struct elemento {
    int info;                   // Valor armazenado no elemento
    struct elemento *prox;     // Ponteiro para o próximo elemento
};
typedef struct elemento Elemento;

// Cria uma lista vazia
Elemento* criar_lista() {
    return NULL;
}

// Insere um novo elemento no final da lista
Elemento* inserir_fim(Elemento *lista, int info) {
    Elemento *novo = malloc(sizeof(Elemento));
    novo->info = info;
    novo->prox = NULL;

    if (lista == NULL)   // Se a lista estiver vazia, retorna o novo elemento
        return novo;

    // Percorre até o final e insere o novo elemento
    Elemento *atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = novo;
    return lista;
}

// Cria uma cópia da lista original
Elemento* copiar_lista(Elemento *origem) {
    Elemento *nova = criar_lista();
    Elemento *atual = origem;
    while (atual != NULL) {
        nova = inserir_fim(nova, atual->info); // Copia cada elemento
        atual = atual->prox;
    }
    return nova;
}

// Imprime todos os elementos da lista
void imprimir_lista(Elemento *lista) {
    Elemento *atual = lista;
    while (atual != NULL) {
        printf("%d ", atual->info);
        atual = atual->prox;
    }
    printf("\n");
}

// Gera uma lista com valores aleatórios de 0 até tamanho - 1
Elemento* gerar_lista_aleatoria(int tamanho) {
    Elemento *lista = criar_lista();
    for (int i = 0; i < tamanho; i++) {
        lista = inserir_fim(lista, rand() % tamanho);
    }
    return lista;
}

// Ordena a lista com Insertion Sort crescente
Elemento* insertionSortCrescente(Elemento *lista) {
    if (lista == NULL || lista->prox == NULL) return lista;

    Elemento *ordenada = NULL;

    while (lista != NULL) {
        Elemento *atual = lista;
        lista = lista->prox;

        // Insere o elemento atual na posição correta da lista ordenada
        if (ordenada == NULL || atual->info < ordenada->info) {
            atual->prox = ordenada;
            ordenada = atual;
        } else {
            Elemento *temp = ordenada;
            while (temp->prox != NULL && temp->prox->info < atual->info) {
                temp = temp->prox;
            }
            atual->prox = temp->prox;
            temp->prox = atual;
        }
    }
    return ordenada;
}

// Ordena a lista com Insertion Sort decrescente
Elemento* insertionSortDecrescente(Elemento *lista) {
    if (lista == NULL || lista->prox == NULL) return lista;

    Elemento *ordenada = NULL;

    while (lista != NULL) {
        Elemento *atual = lista;
        lista = lista->prox;

        // Insere o elemento atual na posição correta (decrescente)
        if (ordenada == NULL || atual->info > ordenada->info) {
            atual->prox = ordenada;
            ordenada = atual;
        } else {
            Elemento *temp = ordenada;
            while (temp->prox != NULL && temp->prox->info > atual->info) {
                temp = temp->prox;
            }
            atual->prox = temp->prox;
            temp->prox = atual;
        }
    }
    return ordenada;
}

// Troca os dados de dois elementos
void trocar(Elemento *a, Elemento *b) {
    int temp = a->info;
    a->info = b->info;
    b->info = temp;
}

// Selection Sort crescente usando troca de dados
Elemento* selectionSortCrescente(Elemento *lista) {
    for (Elemento *i = lista; i != NULL; i = i->prox) {
        Elemento *min = i;
        for (Elemento *j = i->prox; j != NULL; j = j->prox) {
            if (j->info < min->info) {
                min = j;
            }
        }
        trocar(i, min);
    }
    return lista;
}

// Selection Sort decrescente
Elemento* selectionSortDecrescente(Elemento *lista) {
    for (Elemento *i = lista; i != NULL; i = i->prox) {
        Elemento *max = i;
        for (Elemento *j = i->prox; j != NULL; j = j->prox) {
            if (j->info > max->info) {
                max = j;
            }
        }
        trocar(i, max);
    }
    return lista;
}

// Libera a memória
void liberar_lista(Elemento *lista) {
    while (lista != NULL) {
        Elemento *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

// Função principal
int main() {
    int metodo, escolha, tam_vetor;

    printf("ORDENADOR DE NUMEROS\n");
    printf("Seja bem vindo ao ordenador de numeros!\nEsse programa gera uma lista de numeros aleatorios e voce escolhe como ela sera ordenada\n");

    printf("Insira o tamanho da lista que deseja gerar (entre 2 e 9999):\n");
    scanf("%d", &tam_vetor);

    // Verifica se o tamanho é válido
    if (tam_vetor < 2 || tam_vetor > 9999) {
        printf("Valor invalido, encerrando o programa...\n");
        return 1;
    }

    srand(time(NULL)); // Inicializa vetor aleatório

    // Gera a lista
    Elemento *lista_original = gerar_lista_aleatoria(tam_vetor);
    Elemento *lista;

    do {
        lista = copiar_lista(lista_original); // Cria uma cópia

        // Menu
        printf("\nEscolha seu metodo de ordenacao:\n");
        printf("1 - Insertion Sort (Crescente)\n");
        printf("2 - Insertion Sort (Decrescente)\n");
        printf("3 - Selection Sort (Crescente)\n");
        printf("4 - Selection Sort (Decrescente)\n");
        scanf("%d", &metodo);

        printf("Lista original:\n");
        imprimir_lista(lista);

        // Aplica o método escolhido
        switch (metodo) {
            case 1:
                lista = insertionSortCrescente(lista);
                printf("Lista ordenada (Insertion Crescente):\n");
                break;
            case 2:
                lista = insertionSortDecrescente(lista);
                printf("Lista ordenada (Insertion Decrescente):\n");
                break;
            case 3:
                lista = selectionSortCrescente(lista);
                printf("Lista ordenada (Selection Crescente):\n");
                break;
            case 4:
                lista = selectionSortDecrescente(lista);
                printf("Lista ordenada (Selection Decrescente):\n");
                break;
            default:
                printf("Metodo invalido.\n");
                liberar_lista(lista);
                continue;
        }

        imprimir_lista(lista);
        liberar_lista(lista); // Libera a lista

        printf("\nDeseja testar outro metodo?\n1 - Sim\n2 - Nao\n");
        scanf("%d", &escolha);

    } while (escolha == 1);

    liberar_lista(lista_original); // Libera a lista original
    printf("Encerrando o programa...\n");
    return 0;
}
