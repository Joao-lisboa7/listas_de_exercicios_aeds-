#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void copiar_para_binario(const char *nome_csv, const char *nome_binario) {
    FILE *arquivo_csv = fopen(nome_csv, "r");
    if (arquivo_csv == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return;
    }

    FILE *arquivo_bin = fopen(nome_binario, "wb");
    if (arquivo_bin == NULL) {
        printf("Erro ao criar o arquivo binário.\n");
        fclose(arquivo_csv);
        return;
    }

    char buffer[200];
    while (fgets(buffer, sizeof(buffer), arquivo_csv) != NULL) {
        fwrite(buffer, sizeof(char), strlen(buffer), arquivo_bin);
    }

    fclose(arquivo_csv);
    fclose(arquivo_bin);

    printf("Copia concluida com sucesso!\n");
}
int main() {
    copiar_para_binario("iris.csv", "iris.bin");
    return 0;
}
