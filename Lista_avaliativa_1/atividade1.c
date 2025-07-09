/* 1.Implementar um algoritmo que recebe um número inteiro N fornecido pelo usuário e mostre a soma
dos números ímpares de 0 até N (incluindo N, se N for ímpar). */

#include<stdio.h>
#include<math.h>
int main(){
  int num, count = 0, soma;

  printf("Digite um numero: ");
  scanf("%d", &num);

  while(count <= num){
    if(count % 2 != 0){
      //printf("%d \n", count);    teste de para ver se contou os números ímpares
      soma += count;
    }

    count++;
  }

  printf("%d", soma);

  return 0;
}