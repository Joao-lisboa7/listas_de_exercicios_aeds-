#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

typedef struct {
    int count;
    float sepal_length_sum, sepal_width_sum, petal_length_sum, petal_width_sum;
    float sepal_length_min, sepal_width_min, petal_length_min, petal_width_min;
    float sepal_length_max, sepal_width_max, petal_length_max, petal_width_max;
} Estatisticas;

void inicializar_estatisticas(Estatisticas *e) {
    e->count = 0;
    e->sepal_length_sum = e->sepal_width_sum = 0;
    e->petal_length_sum = e->petal_width_sum = 0;

    e->sepal_length_min = e->sepal_width_min = e->petal_length_min = e->petal_width_min = FLT_MAX;
    e->sepal_length_max = e->sepal_width_max = e->petal_length_max = e->petal_width_max = FLT_MIN;
}

void atualizar_estatisticas(Estatisticas *e, float sl, float sw, float pl, float pw) {
    e->count++;
    e->sepal_length_sum += sl;
    e->sepal_width_sum  += sw;
    e->petal_length_sum += pl;
    e->petal_width_sum  += pw;

    if (sl < e->sepal_length_min) e->sepal_length_min = sl;
    if (sw < e->sepal_width_min) e->sepal_width_min = sw;
    if (pl < e->petal_length_min) e->petal_length_min = pl;
    if (pw < e->petal_width_min) e->petal_width_min = pw;

    if (sl > e->sepal_length_max) e->sepal_length_max = sl;
    if (sw > e->sepal_width_max) e->sepal_width_max = sw;
    if (pl > e->petal_length_max) e->petal_length_max = pl;
    if (pw > e->petal_width_max) e->petal_width_max = pw;
}

void salvar_estatisticas(const char *nome_arquivo, Estatisticas *e) {
    FILE *out = fopen(nome_arquivo, "w");
    if (out == NULL) {
        printf("Erro ao criar o arquivo %s\n", nome_arquivo);
        return;
    }

    fprintf(out, "Estatisticas da especie:\n");
    fprintf(out, "Sepal Length - Media: %.2f | Min: %.2f | Max: %.2f\n", e->sepal_length_sum / e->count, e->sepal_length_min, e->sepal_length_max);
    fprintf(out, "Sepal Width  - Media: %.2f | Min: %.2f | Max: %.2f\n", e->sepal_width_sum  / e->count, e->sepal_width_min,  e->sepal_width_max);
    fprintf(out, "Petal Length - Media: %.2f | Min: %.2f | Max: %.2f\n", e->petal_length_sum / e->count, e->petal_length_min, e->petal_length_max);
    fprintf(out, "Petal Width  - Media: %.2f | Min: %.2f | Max: %.2f\n", e->petal_width_sum  / e->count, e->petal_width_min,  e->petal_width_max);

    fclose(out);
}

void processar_arquivo(const char *nome_arquivo) {
    FILE *entrada = fopen(nome_arquivo, "r");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Estatisticas setosa, versicolor, virginica;
    inicializar_estatisticas(&setosa);
    inicializar_estatisticas(&versicolor);
    inicializar_estatisticas(&virginica);

    char linha[200];
    fgets(linha, sizeof(linha), entrada);

    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        char *token;
        float sl, sw, pl, pw;
        char especie[50];

        token = strtok(linha, ","); sl = atof(token);
        token = strtok(NULL, ","); sw = atof(token);
        token = strtok(NULL, ","); pl = atof(token);
        token = strtok(NULL, ","); pw = atof(token);
        token = strtok(NULL, ",\n\r"); strcpy(especie, token);

        if (strcmp(especie, "setosa") == 0) {
            atualizar_estatisticas(&setosa, sl, sw, pl, pw);
        } else if (strcmp(especie, "versicolor") == 0) {
            atualizar_estatisticas(&versicolor, sl, sw, pl, pw);
        } else if (strcmp(especie, "virginica") == 0) {
            atualizar_estatisticas(&virginica, sl, sw, pl, pw);
        }
    }

    fclose(entrada);

    salvar_estatisticas("setosa_dados.txt", &setosa);
    salvar_estatisticas("versicolor_dados.txt", &versicolor);
    salvar_estatisticas("virginica_dados.txt", &virginica);

    printf("Estatisticas salvas com sucesso!\n");
}

int main() {
    char nome_arquivo[100];

    printf("Digite o nome do arquivo: ");
    scanf("%99s", nome_arquivo);

    processar_arquivo(nome_arquivo);

    return 0;
}
