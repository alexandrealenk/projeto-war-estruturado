#include <stdio.h>
#include <string.h>

#define MAX_TERRITORIOS 5
#define TAM_STRING 100

struct territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
        struct territorio mapa[MAX_TERRITORIOS];
        int totalterrritorios = 0;

        printf("==============================\n\n");
        printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n\n");
        
       // Cadastro de todos os territórios
    for (totalterrritorios = 0; totalterrritorios < MAX_TERRITORIOS; totalterrritorios++) {
        printf("== Cadastrando territorio %d ==\n", totalterrritorios + 1);

        printf("Digite o nome do territorio: ");
        fgets(mapa[totalterrritorios].nome, TAM_STRING, stdin);
        mapa[totalterrritorios].nome[strcspn(mapa[totalterrritorios].nome, "\n")] = 0;

        printf("Digite a cor do exercito: ");
        fgets(mapa[totalterrritorios].cor, TAM_STRING, stdin);
        mapa[totalterrritorios].cor[strcspn(mapa[totalterrritorios].cor, "\n")] = 0;

        printf("Numero de tropas: ");
        scanf("%d", &mapa[totalterrritorios].tropas);
        limparBuffer();
    }
            // Exemplo: mostrar os territórios cadastrados
        printf("\nTerritorios cadastrados:\n");
        for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("%d. Nome: %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
 
            return 0;
        }
}