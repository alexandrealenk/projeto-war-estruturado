#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5
#define NUM_MISSOES 3

// Estrutura para armazenar dados de um território
typedef struct {
    char nome[30];
    char cor[15];
    int tropas;
} Territorio;

// Função para inicializar territórios automaticamente
void inicializarTerritorios(Territorio* mapa) {
    const char* nomes[NUM_TERRITORIOS] = {"America", "Europa", "Asia", "Africa", "Oceania"};
    const char* cores[NUM_TERRITORIOS] = {"azul", "verde", "vermelho", "amarelo", "branco"};
    const int tropas[NUM_TERRITORIOS] = {5, 3, 2, 4, 1};
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = tropas[i];
    }
}

// Exibe o estado atual do mapa
void exibirMapa(const Territorio* mapa, int tamanho) {
    printf("\n=========== MAPA DO MUNDO ==========\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %s |Exercito: %s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("=====================================\n");
}

// Função para atribuir missão aleatória
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// Função para simular ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;
    printf("\n%s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtq, dadoDef);
    if (dadoAtq >= dadoDef) {
        defensor->tropas--;
        printf("O defensor perde 1 tropa!\n");
        if (defensor->tropas <= 0) {
            // conquista: garante 1 tropa no defensor e atualiza cor; move 1 tropa do atacante
            defensor->tropas = 1;
            strcpy(defensor->cor, atacante->cor);
            if (atacante->tropas > 0) atacante->tropas--; // mover 1 tropa (se possível)
            printf("Territorio conquistado pelo atacante!\n");
        }
    } else {
        // atacante perde 1 tropa em caso de fracasso
        if (atacante->tropas > 0) atacante->tropas--;
        printf("O ataque falhou. Atacante perde 1 tropa.\n");
    }
}

// Verifica se a missão foi cumprida
int verificarMissao(const char* missao, const Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Destruir o exercito Verde") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "verde") == 0 && mapa[i].tropas > 0) return 0;
        }
        return 1;
    }
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        int countAzul = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) countAzul++;
        }
        if (countAzul >= 3) return 1;
        return 0;
    }
    //eliminar o exercito vermelho
    if (strcmp(missao, "Eliminar o exercito vermelho") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0) return 0;
        }
        return 1;
    }
    return 0;
}

// Exibe a missão do jogador
void exibirMissao(const char* missao) {
    printf("\nMissao do jogador: %s\n", missao);
}

int main() {
    srand((unsigned int)time(NULL));
    Territorio mapa[NUM_TERRITORIOS];
    inicializarTerritorios(mapa);
    const char* missoesDisponiveis[NUM_MISSOES] = {
        "Destruir o exercito Verde",
        "Conquistar 3 territorios",
        "Eliminar o exercito vermelho"
    };
    char missao[50];
    atribuirMissao(missao, missoesDisponiveis, NUM_MISSOES);
    exibirMissao(missao);
    int opcao;
    int venceu = 0;
    do {
        exibirMapa(mapa, NUM_TERRITORIOS);
        printf("\nMenu Principal:\n1 - Atacar\n2 - Verificar Missao\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
            case 1: {
                int atq, def;
                printf("Escolha o territorio atacante (1 a %d): ", NUM_TERRITORIOS);
                scanf("%d", &atq);
                printf("Escolha o territorio defensor (1 a %d): ", NUM_TERRITORIOS);
                scanf("%d", &def);
                getchar();
                if (atq < 1 || atq > NUM_TERRITORIOS || def < 1 || def > NUM_TERRITORIOS || atq == def) {
                    printf("Escolha invalida.\n");
                } else if (mapa[atq-1].tropas <= 1) {
                    // requer pelo menos 2 tropas para atacar (1 deve permanecer)
                    printf("Territorio atacante nao tem tropas suficientes para atacar (precisa de >1 tropa).\n");
                } else {
                    atacar(&mapa[atq-1], &mapa[def-1]);
                    if (verificarMissao(missao, mapa, NUM_TERRITORIOS)) {
                        venceu = 1;
                        printf("\nParabens! Voce cumpriu sua missao: %s\n", missao);
                    }
                }
                break;
            }
            case 2:
                exibirMissao(missao);
                if (verificarMissao(missao, mapa, NUM_TERRITORIOS)) {
                    printf("\nMissao cumprida! Voce venceu!\n");
                    venceu = 1;
                } else {
                    printf("\nMissao ainda nao cumprida.\n");
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opçao invalida.\n");
        }
    } while (opcao != 0 && !venceu);
    if (venceu) printf("\n=== Fim de jogo ===\n");
    return 0;
}