//bibliotecas
#include <stdio.h>
#include <string.h>

//Constantes
#define MAX_TERRITORIOS 5
#define TAM_STRING 100

//Estruturas
struct territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

//Função para limpar o buffer, assim evita prejuízos na leitura de caracteres residuais.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função principal: foi criado um array de estruturas para armazenar os territórios.
int main() {
        struct territorio mapa[MAX_TERRITORIOS];
        int totalterrritorios = 0;

//Mensagem principal de inicio do programa.
        printf("\n========================================================\n");
        printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");
        
// Cadastro de todos os territórios utilizando um laço for.
        for (totalterrritorios = 0; totalterrritorios < MAX_TERRITORIOS; totalterrritorios++) {
        printf("\n== Cadastrando territorio %d ==\n", totalterrritorios + 1);

        printf("Digite o nome do territorio: ");
        fgets(mapa[totalterrritorios].nome, TAM_STRING, stdin);
        mapa[totalterrritorios].nome[strcspn(mapa[totalterrritorios].nome, "\n")] = 0;

        printf("Digite a cor do exercito: ");
        fgets(mapa[totalterrritorios].cor, TAM_STRING, stdin);
        mapa[totalterrritorios].cor[strcspn(mapa[totalterrritorios].cor, "\n")] = 0;

        printf("Numero de tropas: ");
        scanf("%d", &mapa[totalterrritorios].tropas);
        limparBuffer();
// Limpa o buffer para evitar problemas na próxima leitura.

// Confirmação de cadastro.
        }
        printf ("\nCadastro inicial concluido com sucesso!\n");

//Mostra todos os territórios cadastrados com todas as informações.
        printf("\n===============================\n");
        printf("  MAPA DO MUNDO - ESTADO ATUAL\n");
        printf("===============================\n\n");
//O laço for percorre o array de estruturas e imprime as informações de cada território.
        for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Territorio %d:\n - Nome: %s\n - Dominado por: Exercito %s\n - Tropas: %d\n\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }

        return 0;
}