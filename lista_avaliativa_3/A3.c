#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void separar_especies(const char *nome_arquivo) {
    FILE *entrada = fopen(nome_arquivo, "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    }

    FILE *arquivo_setosa = fopen("setosa.csv", "w");
    FILE *arquivo_versicolor = fopen("versicolor.csv", "w");
    FILE *arquivo_virginica = fopen("virginica.csv", "w");

    if (arquivo_setosa == NULL || arquivo_versicolor == NULL || arquivo_virginica == NULL) {
        printf("Erro ao criar arquivos de saída.\n");
        fclose(entrada);
        return;
    }

    char linha[256];
    
    if (fgets(linha, sizeof(linha), entrada) != NULL) {
        fprintf(arquivo_setosa, "%s", linha);
        fprintf(arquivo_versicolor, "%s", linha);
        fprintf(arquivo_virginica, "%s", linha); 
    }  

    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        char copia[256];
        strcpy(copia, linha);

        copia[strcspn(copia, "\n\r")] = '\0'; 
 
        char *token = strtok(copia, ",");
        char *especie = NULL;     
    
        while (token != NULL) {
            especie = token;
            token = strtok(NULL, ",");
        }
 
        if (especie == NULL) continue;
    
        if (strcmp(especie, "setosa") == 0) {
            fprintf(arquivo_setosa, "%s", linha);
        } else if (strcmp(especie, "versicolor") == 0) { 
            fprintf(arquivo_versicolor, "%s", linha);
        } else if (strcmp(especie, "virginica") == 0) {
            fprintf(arquivo_virginica, "%s", linha);
        }
    }

    fclose(entrada);
    fclose(arquivo_setosa);
    fclose(arquivo_versicolor);
    fclose(arquivo_virginica);

    printf("Dados separados com sucesso em setosa.csv, versicolor.csv e virginica.csv.\n");
}

int main() {
    char nome_arquivo[100];

    printf("Digite o nome do arquivo: ");
    scanf("%99s", nome_arquivo);

    separar_especies(nome_arquivo);

    return 0;
}
