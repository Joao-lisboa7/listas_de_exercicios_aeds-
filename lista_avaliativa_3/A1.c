#include<stdio.h>
#include<math.h>
#include<stdlib.h>
void contar_linhas(const char *nome_arquivo){
  FILE *arquivo = fopen(nome_arquivo, "r");

  if(arquivo == NULL){
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  int linhas = 0;
  char caractere;

  
  while ((caractere = fgetc(arquivo)) != EOF) {
    if(caractere == '\n'){
      linhas++;
    }
  }

  fclose(arquivo);
  printf("O arquivo tem: %d linhas", linhas);
}

int main(){
  char nome_arquivo[100];

  printf("Digite o nome do arquivo: ");
  scanf("%99s", nome_arquivo);

  contar_linhas(nome_arquivo);
}