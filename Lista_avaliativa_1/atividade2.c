/* 2.Implementar um algoritmo que solicita um número inteiro ao usuário, calcule e mostre o seu
fatorial. */
#include<stdio.h>
#include<math.h>
int main(){
  int num, fatorial = 1;

  printf("Digite um numero: ");
  scanf("%d", &num);

  while(num > 0){
    fatorial *= num;
    num--;
  }

  printf("%d", fatorial);

  return 0;
}