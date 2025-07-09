#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAM 200
#define MAX_PALAVRAS 50
#define TAM_PALAVRA 20

void contarRepetidas(char *texto) {
  char palavras[MAX_PALAVRAS][TAM_PALAVRA];
  int contagem[MAX_PALAVRAS] = {0};
  int total = 0;
 
  char *palavra = strtok(texto, " \n");

  while (palavra != NULL) {
    int achou = 0;
 
    for (int i = 0; palavra[i]; i++) {
      palavra[i] = tolower(palavra[i]);
    }

    for (int i = 0; i < total; i++) {
      if (strcmp(palavras[i], palavra) == 0) {
        contagem[i]++;
        achou = 1;
        break;
      }
   }

    if (!achou) {
      strcpy(palavras[total], palavra);
      contagem[total] = 1;
      total++;
    }
  
    palavra = strtok(NULL, " \n");
 }
 
  printf("\nPalavras repetidas:\n");
  for (int i = 0; i < total; i++) {
    if (contagem[i] > 1) {
      printf("%s: %d vezes\n", palavras[i], contagem[i]);
    }
  }
}

int main() {
  char texto[TAM];
    
  printf("Digite um texto: ");
  fgets(texto, TAM, stdin);
  
  contarRepetidas(texto);
 
  return 0;
}
