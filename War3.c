#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_TERRITORIOS 5

typedef struct {
    char nome[30];
    char cor[20];
    int tropas;
    int dono; // 0 = sem dono, 1 = jogador
} Territorio;

// =====================
// Função utilitária
// =====================
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// =====================
// Inicializa territórios automaticamente
// =====================
void inicializarTerritorios(Territorio *territorios) {
    const char *nomes[TOTAL_TERRITORIOS] = {
        "Vale Verde", "Montanha Azul", "Deserto Escarlate", "Floresta Negra", "Ilha Amarela"
    };

    const char *cores[TOTAL_TERRITORIOS] = {
        "Verde", "Azul", "Vermelho", "Preto", "Verde"
    };

    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].cor, cores[i]);
        territorios[i].tropas = rand() % 4 + 2; // entre 2 e 5 tropas
        territorios[i].dono = 0; // neutro no início
    }

    // Atribuir 2 territórios iniciais ao jogador
    int atribuicoes = 0;
    while (atribuicoes < 2) {
        int idx = rand() % TOTAL_TERRITORIOS;
        if (territorios[idx].dono == 0) {
            territorios[idx].dono = 1;
            atribuicoes++;
        }
    }
}

// =====================
// Exibe o mapa
// =====================
void exibirMapa(const Territorio *territorios) {
    printf("\n===== Estado Atual do Mapa =====\n");
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Território %d: %s\n", i + 1, territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("  Dono: %s\n", territorios[i].dono == 1 ? "Jogador" : "Inimigo");
        printf("-------------------------------\n");
    }
}

// =====================
// Simula o ataque entre dois territórios
// =====================
void realizarAtaque(Territorio *territorios) {
    int atq, def;

    exibirMapa(territorios);

    printf("Digite o número do território ATACANTE (1-5): ");
    scanf("%d", &atq);
    printf("Digite o número do território DEFENSOR (1-5): ");
    scanf("%d", &def);
    limparBufferEntrada();

    atq--; def--; // ajustar para índice do vetor

    if (atq < 0 || atq >= TOTAL_TERRITORIOS || def < 0 || def >= TOTAL_TERRITORIOS) {
        printf("❌ Território inválido!\n");
        return;
    }

    if (atq == def) {
        printf("❌ Um território não pode atacar a si mesmo!\n");
        return;
    }

    if (territorios[atq].dono != 1) {
        printf("❌ Você só pode atacar de territórios seus.\n");
        return;
    }

    if (territorios[def].dono == 1) {
        printf("❌ Você não pode atacar seus próprios territórios.\n");
        return;
    }

    if (territorios[atq].tropas < 1) {
        printf("❌ Tropas insuficientes para atacar!\n");
        return;
    }

    // Dados de ataque e defesa
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n🎲 Dados Rolados: Jogador (ATK): %d | Inimigo (DEF): %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {
        territorios[def].tropas--;
        printf("✅ Ataque bem-sucedido! Tropas inimigas restantes: %d\n", territorios[def].tropas);
        if (territorios[def].tropas <= 0) {
            printf("🏳️ Território conquistado!\n");
            territorios[def].dono = 1;
            territorios[def].tropas = 1;
            territorios[atq].tropas--;
        }
    } else {
        territorios[atq].tropas--;
        printf("❌ Defesa bem-sucedida. Suas tropas restantes: %d\n", territorios[atq].tropas);
    }
}

// =====================
// Conta territórios por cor
// =====================
int contarTerritoriosPorCor(const Territorio *territorios, const char *cor) {
    int total = 0;
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        if (strcmp(territorios[i].cor, cor) == 0) {
            total++;
        }
    }
    return total;
}

// =====================
// Conta territórios por dono
// =====================
int contarTerritoriosPorDono(const Territorio *territorios, int dono) {
    int total = 0;
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        if (territorios[i].dono == dono) {
            total++;
        }
    }
    return total;
}

// =====================
// Verifica se a missão foi cumprida
// =====================
int verificarMissao(const Territorio *territorios, int tipoMissao) {
    switch (tipoMissao) {
        case 1: // Destruir o exército Verde
            for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
                if (strcmp(territorios[i].cor, "Verde") == 0 &&
                    territorios[i].dono != 1) {
                    return 0; // Ainda existe território verde inimigo
                }
            }
            return 1;

        case 2: // Conquistar 3 territórios
            return contarTerritoriosPorDono(territorios, 1) >= 3;

        default:
            return 0;
    }
}

// =====================
// Exibe a missão do jogador
// =====================
void exibirMissao(int tipoMissao) {
    printf("\n🎯 Sua missão: ");
    switch (tipoMissao) {
        case 1:
            printf("Destruir todos os territórios do exército Verde.\n");
            break;
        case 2:
            printf("Conquistar pelo menos 3 territórios.\n");
            break;
        default:
            printf("Missão desconhecida.\n");
    }
}

// =====================
// Exibe o menu principal
// =====================
int menuPrincipal() {
    int opcao;
    printf("\n===== MENU =====\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar missão\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    limparBufferEntrada();
    return opcao;
}

// =====================
// Função principal
// =====================
int main() {
    srand(time(NULL)); // Inicializar aleatoriedade

    Territorio *territorios = (Territorio *)calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
    if (!territorios) {
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    inicializarTerritorios(territorios);

    // Sorteia missão: 1 ou 2
    int missao = rand() % 2 + 1;

    int fim = 0;
    while (!fim) {
        int opcao = menuPrincipal();

        switch (opcao) {
            case 1:
                realizarAtaque(territorios);
                if (verificarMissao(territorios, missao)) {
                    printf("\n🏆 Parabéns! Você cumpriu sua missão e venceu o jogo!\n");
                    fim = 1;
                }
                break;

            case 2:
                exibirMissao(missao);
                break;

            case 0:
                fim = 1;
                break;

            default:
                printf("❌ Opção inválida.\n");
        }
    }

    free(territorios);
    printf("👋 Jogo encerrado. Obrigado por jogar!\n");
    return 0;
}