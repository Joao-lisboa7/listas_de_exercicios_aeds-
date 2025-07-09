#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    int dia, mes, ano;
} Pessoa;

int comparar_datas(Pessoa a, Pessoa b) {
    if (a.ano != b.ano) return a.ano - b.ano;
    if (a.mes != b.mes) return a.mes - b.mes;
    return a.dia - b.dia;
}

void salvar_em_arquivo(const char *arquivo, Pessoa mais_nova, Pessoa mais_velha) {
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return;
    }

    fprintf(fp, "Mais nova: %s (%02d/%02d/%04d)\n", mais_nova.nome, mais_nova.dia, mais_nova.mes, mais_nova.ano);
    fprintf(fp, "Mais velha: %s (%02d/%02d/%04d)\n", mais_velha.nome, mais_velha.dia, mais_velha.mes, mais_velha.ano);

    fclose(fp);
    printf("Dados salvos com sucesso no arquivo!\n");
}

void visualizar_arquivo(const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[200];
    printf("\nConteudo do arquivo:\n");
    while (fgets(linha, sizeof(linha), fp) != NULL) {
        printf("%s", linha);
    }

    fclose(fp);
}

int main() {
    Pessoa pessoas[6];
    const char *arquivo = "resultado.txt";

    printf("Digite os dados de 6 pessoas (nome e data de nascimento):\n");
    for (int i = 0; i < 6; i++) {
        printf("\nPessoa %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", pessoas[i].nome);

        printf("Data de nascimento (dd mm aaaa): ");
        scanf("%d %d %d", &pessoas[i].dia, &pessoas[i].mes, &pessoas[i].ano);
    }

    Pessoa mais_nova = pessoas[0];
    Pessoa mais_velha = pessoas[0];

    for (int i = 1; i < 6; i++) {
        if (comparar_datas(pessoas[i], mais_nova) > 0) {
            mais_nova = pessoas[i];
        }
        if (comparar_datas(pessoas[i], mais_velha) < 0) {
            mais_velha = pessoas[i];
        }
    }

    salvar_em_arquivo(arquivo, mais_nova, mais_velha);

    char opcao;
    printf("\nDeseja visualizar os dados do arquivo? (s/n): ");
    scanf(" %c", &opcao);
    if (opcao == 's' || opcao == 'S') {
        visualizar_arquivo(arquivo);
    }

    return 0;
}
