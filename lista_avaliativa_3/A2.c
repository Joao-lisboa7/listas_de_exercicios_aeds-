#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
void conta_amostras(const char *nome_arquivo){
  FILE *arquivo = fopen(nome_arquivo, "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  char linha[200];
  int setosa = 0, versicolor = 0, virginica = 0;

  while(fgets(linha, sizeof(linha), arquivo) != NULL){
    linha[strcspn(linha, "\n")] = '\0';

    char *token = strtok(linha, ",");
    char *especie = NULL;

    while (token != NULL) {
      especie = token;
      token = strtok(NULL, ",");
    }

    if(strcmp(especie, "setosa") == 0) {
      setosa++;
    }else if (strcmp(especie, "versicolor") == 0) {
      versicolor++;
    }else if (strcmp(especie, "virginica") == 0) {
      virginica++;
    }
  }

  fclose(arquivo);

  printf("Quantidade de amostras por especie:\n");
  printf("Iris-setosa: %d\n", setosa);
  printf("Iris-versicolor: %d\n", versicolor);
  printf("Iris-virginica: %d\n", virginica);
}
int main(){
  char nome_arquivo[100];

  printf("Digite o nome do arquivo: ");
  scanf("%99s", nome_arquivo);

  conta_amostras(nome_arquivo);

  return 0;
}