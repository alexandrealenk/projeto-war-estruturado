/*
    Programa: WAR Estruturado - Fase de Ataque
    Objetivo: Implementar um sistema interativo de territórios com simulação de ataques.

    Funcionalidades:
    - Cadastro dinâmico de territórios usando ponteiros
    - Exibição dos territórios cadastrados
    - Função de ataque com simulação aleatória (dados)
    - Atualização de cores e tropas após o ataque
    - Liberação de memória ao final 
*/
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5

// ============================
// Struct para representar um território
// ============================
typedef struct {
    char nome[30];
    char cor[20];
    int tropas;
} Territorio;

// ============================
// Remove '\n' do final da string
// ============================
void limparNovaLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// ============================
// Limpa o buffer do teclado após scanf
// ============================
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ============================
// Função para cadastrar territórios
// ============================
void cadastrarTerritorios(Territorio *territorios) {
    printf("===== Cadastro de Territorios =====\n\n");

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Territorio %d:\n", i + 1);

        printf("Nome do territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        limparNovaLinha(territorios[i].nome);

        printf("Cor do exercito: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        limparNovaLinha(territorios[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada();

        printf("\n");
    }
}

// ============================
// Função para exibir o estado atual do mapa
// ============================
void exibirMapa(Territorio *territorios) {
    printf("\n===== Estado Atual do Mapa =====\n\n");
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("%d. ", i + 1); // Número do território
        printf("%s ", territorios[i].nome);
        printf("(Exercito %s,", territorios[i].cor);
        printf("Tropas: %d)", territorios[i].tropas);
    }
}

// ============================
// Função para simular um ataque
// ============================
int simularAtaque(Territorio *territorios) {
    int atacante, defensor;

    printf("\n===== Fase de Ataque =====\n");
    printf("Escolha o numero do territorio atacante (1 a 5) ou 0 para sair: ");
    scanf("%d", &atacante);
    if (atacante == 0) {
        return 0; // sinaliza que o jogador quer sair
    }
    printf("Escolha o numero do territorio defensor (1 a 5): ");
    scanf("%d", &defensor);
    limparBufferEntrada();

    atacante--; defensor--; // Ajustar índice

    // Verificações básicas
    if (atacante < 0 || atacante >= TOTAL_TERRITORIOS ||
        defensor < 0 || defensor >= TOTAL_TERRITORIOS) {
        printf("Território invalido!\n");
        return 1; //continuar o loop, não encerra o jogo
    }

    if (atacante == defensor) {
        printf("Um território não pode atacar a si mesmo!\n");
        return 1;
    }

    if (territorios[atacante].tropas < 1) {
        printf("Territorio atacante não tem tropas suficientes!\n");
        return 1;
    }

    // Simular dados
    int dadoAtq = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\n=== RESULTADO DA BATALHA ===\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", territorios[atacante].nome, dadoAtq);
    printf("O Defensor %s rolou um dado e tirou: %d\n", territorios[defensor].nome, dadoDef);

    // Comparar dados
    if (dadoAtq >= dadoDef) {
        territorios[defensor].tropas--;
        printf("Vitoria do atacante! Defensor perdeu 1 tropa.\n");

        if (territorios[defensor].tropas <= 0) {
            printf("Territorio conquistado!");
            printf(" %s conquistou %s!\n", territorios[atacante].nome, territorios[defensor].nome);
            territorios[defensor].tropas = 1; // Mover 1 tropa para o território conquistado
            territorios[atacante].tropas--;   // Reduzir 1 tropa do atacante
        }
    } else {
        territorios[atacante].tropas--;
        printf("Vitoria da defesa! Atacante perdeu 1 tropa.\n");
    }
    return 1; // continuar o jogo
}

// ============================
// Função principal
// ============================
int main() {
    srand(time(NULL)); // Inicializa semente aleatória

    printf("\n=========================================\n");
    printf("WAR ESTRUTURADO - CADASTRO INICIAL\n");
    printf("=========================================\n\n");

    // Alocação dinâmica com calloc
    Territorio *territorios = (Territorio *)calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(territorios);

    // Exibe o mapa e realiza um único ataque
    
   // Agora o loop principal depende do retorno de simularAtaque
    while (simularAtaque(territorios)) {
        exibirMapa(territorios);
        printf("\nPressione Enter para continuar o próximo turno...");
        getchar(); // Espera o Enter
    }

    // Libera memória
    free(territorios);
    printf("\nFim do jogo. Memoria liberada.\n");

    return 0;
}