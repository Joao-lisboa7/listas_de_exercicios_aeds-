#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
char* capitalizeString(char *vetor, int tamanho) {
  char *novaString = (char *) malloc((tamanho + 1) * sizeof(char));
 
  if (novaString == NULL) {
    printf("Erro ao alocar memória.\n");
    return NULL;
  }

  for (int i = 0; i < tamanho; i++) {
    novaString[i] = toupper(vetor[i]);
  }
  
  novaString[tamanho] = '\0';

  return novaString;
}

int main() {
  char texto[100];

  printf("Digite um texto: ");
  fgets(texto, sizeof(texto), stdin);
  texto[strcspn(texto, "\n")] = '\0';
 
  char *resultado = capitalizeString(texto, strlen(texto));

  if (resultado != NULL) {
    printf("Texto em maiusculas: %s\n", resultado);
    free(resultado);
  }

  return 0;
}
