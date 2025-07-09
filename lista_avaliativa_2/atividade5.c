#include <stdio.h>
#include <ctype.h>
#include <string.h>
int validar(char *email){
  int tamanho = strlen(email);

  for(int i = 0; i < tamanho; i++){
    if(email[i] == '@'){
      printf("valido \nO @ esta na posicao: %d", i + 1);
      return i;
    }
  }

  printf("Invalido");
  return -1;
}
int main(){
  char email[20];

  printf("Digite seu email: ");
  fgets(email, 20, stdin);
  email[strcspn(email, "\n")] = '\0';

  validar(email);

  return 0;
}