#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar o mapa e suas dimensões
typedef struct {
    int **mapa;
    int L, C;
} Mapa;

// Função para alocar memória para o mapa
Mapa* criarMapa(int L, int C) {
    Mapa *m = (Mapa*)malloc(sizeof(Mapa));
    m->L = L;
    m->C = C;
    m->mapa = (int**)malloc(L * sizeof(int*));
    for (int i = 0; i < L; i++) {
        m->mapa[i] = (int*)malloc(C * sizeof(int));
    }
    return m;
}

// Função para liberar a memória do mapa
void liberarMapa(Mapa *m) {
    for (int i = 0; i < m->L; i++) {
        free(m->mapa[i]);
    }
    free(m->mapa);
    free(m);
}

// Função para ler o mapa do arquivo
void lerMapa(FILE *arquivo, Mapa *m) {
    for (int i = 0; i < m->L; i++) {
        for (int j = 0; j < m->C; j++) {
            fscanf(arquivo, "%d", &m->mapa[i][j]);
        }
    }
}

// Função para a Tarefa #1
int maiorEnergiaPositiva(Mapa *m, int l, int c, int k) {
    int maior = 0;
    for (int i = l - k; i <= l + k; i++) {
        for (int j = c - k; j <= c + k; j++) {
            if (i >= 0 && i < m->L && j >= 0 && j < m->C && m->mapa[i][j] > maior) {
                maior = m->mapa[i][j];
            }
        }
    }
    return maior;
}

// Função para a Tarefa #2
int somaEnergiaPositiva(Mapa *m, int l, int c, int k) {
    int soma = 0;
    for (int i = l - k; i <= l + k; i++) {
        for (int j = c - k; j <= c + k; j++) {
            if (i >= 0 && i < m->L && j >= 0 && j < m->C && m->mapa[i][j] > 0) {
                soma += m->mapa[i][j];
            }
        }
       }
    return soma;
}

// Função para a Tarefa #3
void caminhoVerticalHorizontal(int l1, int c1, int l2, int c2, FILE *saida) {
    while (l1 != l2) {
        l1 += (l2 > l1) ? 1 : -1;
        fprintf(saida, "(%d, %d)\n", l1, c1);
    }
    while (c1 != c2) {
        c1 += (c2 > c1) ? 1 : -1;
        fprintf(saida, "(%d, %d)\n", l1, c1);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        return 0;
    }

    FILE *entrada = fopen(argv[1], "r");
    if (!entrada) {
        return 0;
    }

    char nome_arquivo_saida[256];
    snprintf(nome_arquivo_saida, sizeof(nome_arquivo_saida), "%s.sol1maps", argv[1]);
    FILE *saida = fopen(nome_arquivo_saida, "w");
    if (!saida) {
        fclose(entrada);
        return 0;
    }

    int L, C, l, c, k, l2, c2;
    while (fscanf(entrada, "%d %d %d %d %d", &L, &C, &l, &c, &k) != EOF) {
        // Escrever o cabeçalho no ficheiro de saída
        if (k == 0) {
            fscanf(entrada, "%d %d", &l2, &c2);
            fprintf(saida, "%d %d %d %d %d %d %d\n", L, C, l, c, k, l2, c2);
        } else {
            fprintf(saida, "%d %d %d %d %d\n", L, C, l, c, k);
        }

        Mapa *m = criarMapa(L, C);
        lerMapa(entrada, m);

        if (k < 0) {
            int resultado = maiorEnergiaPositiva(m, l, c, -k);
            if (l >= 1 && l <= L && c >= 1 && c <= C) {
                fprintf(saida, "%d %d %d %d %d %d\n", L, C, l, c, k, resultado);
            }
        } else if (k > 0) {
            int resultado = somaEnergiaPositiva(m, l, c, k);
            if (l >= 1 && l <= L && c >= 1 && c <= C) {
                fprintf(saida, "%d %d %d %d %d %d\n", L, C, l, c, k, resultado);
            }
        } else {
            if (l >= 1 && l <= L && c >= 1 && c <= C && l2 >= 1 && l2 <= L && c2 >= 1 && c2 <= C) {
                caminhoVerticalHorizontal(l, c, l2, c2, saida);
            }
        }

        liberarMapa(m);
        fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
