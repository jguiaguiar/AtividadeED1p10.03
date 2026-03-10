#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contato {
    char nome[128];
    char telefone[32];
};

void adicionar(struct Contato agenda[], int *total);
void exibir(struct Contato agenda[], int total);
void salvar(struct Contato agenda[], int total);
void carregar(struct Contato agenda[], int *total);

int main() {
    const int MAX_CONTATOS = 100;
    struct Contato agenda[MAX_CONTATOS];
    int totalContatos = 0;
    int opcao;

    carregar(agenda, &totalContatos);

    do {
        printf("\n AGENDA \n");
        printf("1- Adicionar contato\n");
        printf("2- Exibir contatos\n");
        printf("3- Salvar e sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        if (opcao == 1) {
            if (totalContatos < MAX_CONTATOS) {
                adicionar(agenda, &totalContatos);
            } else {
                printf("Agenda lotada\n");
            }
        } else if (opcao == 2) {
            exibir(agenda, totalContatos);
        }

    } while (opcao != 3);

    salvar(agenda, totalContatos);
    printf("Dados salvos\n");

    return 0;
}

void adicionar(struct Contato agenda[], int *total) {
    printf("Nome: ");
    fgets(agenda[*total].nome, 128, stdin);
    agenda[*total].nome[strcspn(agenda[*total].nome, "\n")] = 0;

    printf("Telefone (dd) xxxxx-xxxx: ");
    fgets(agenda[*total].telefone, 32, stdin);
    agenda[*total].telefone[strcspn(agenda[*total].telefone, "\n")] = 0;

    (*total)++;
    printf("Contato adicionado\n");
}

void exibir(struct Contato agenda[], int total) {
    if (total == 0) {
        printf("Agenda vazia\n");
        return;
    }
    printf("\nLISTA DE CONTATOS\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s - %s\n", i + 1, agenda[i].nome, agenda[i].telefone);
    }
}

void salvar(struct Contato agenda[], int total) {
    FILE *arquivo = fopen("agenda.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrta\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s,%s\n", agenda[i].nome, agenda[i].telefone);
    }

    fclose(arquivo);
}

void carregar(struct Contato agenda[], int *total) {
    FILE *arquivo = fopen("agenda.csv", "r");
    if (arquivo == NULL) {
        return;
    }

    while (fscanf(arquivo, " %127[^,],%31[^\n]\n", agenda[*total].nome, agenda[*total].telefone) == 2) {
        (*total)++;
        if (*total >= 100) break;
    }

    fclose(arquivo);
    printf("Contatos carregados: %d\n", *total);
}