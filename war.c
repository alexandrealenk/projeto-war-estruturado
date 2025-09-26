#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define TAM_STRING 100

struct territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct territorio mapa[MAX_TERRITORIOS];
    int totalTerritorios = 0;
    int opcao;

    do {
        printf("===============================\n");
        printf("          JOGO WAR\n");
        printf("===============================\n");
        printf("1 - Cadastrar novo territorio\n");
        printf("2 - Listar todos os territorios\n");
        printf("0 - Sair\n");
        printf("===============================\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                printf("=== Cadastro de novo territorio ===\n");
                
                if (totalTerritorios < MAX_TERRITORIOS) {
                    printf("Digite o nome do territorio: ");
                    fgets(mapa[totalTerritorios].nome, TAM_STRING, stdin);
                   

                    printf("Digite a cor do territorio: ");
                    fgets(mapa[totalTerritorios].cor, TAM_STRING, stdin);
                   

                     mapa[totalTerritorios].nome[strcspn(mapa[totalTerritorios].nome, "\n")] = 0;
                     mapa[totalTerritorios].cor[strcspn(mapa[totalTerritorios].cor, "\n")] = 0;
                    
                    printf("Digite o numero de tropas: ");
                    scanf("%d", &mapa[totalTerritorios].tropas);
                    limparBufferEntrada();

                    totalTerritorios++;

                    printf("\nTerritorio cadastrado com sucesso!\n");
                } else {
                    printf("Limite de territorios atingido!\n");
                }
                break;

            case 2:
                printf("=== Lista de territorios cadastrados ===\n");
                if (totalTerritorios == 0) {
                    printf("Nenhum territorio cadastrado.\n");
                } else {
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("Territorio %d:\n", i + 1);
                        printf("Nome: %s\n", mapa[i].nome);
                        printf("Cor: %s\n", mapa[i].cor);
                        printf("Numero de tropas: %d\n", mapa[i].tropas);
                    }
                    printf("-------------------------------\n");
                }

                printf("pressione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }
    } while (opcao != 0);

    return 0;
}