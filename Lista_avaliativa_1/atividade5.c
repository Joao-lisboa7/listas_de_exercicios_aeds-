/* 5.Desenvolva um algoritmo que imprima os n primeiros elementos da série de Fibonacci. */
#include<stdio.h>
#include<math.h>
int main(){
  int num, count = 1, f = 1, fant = 0;

  printf("Digite o numero desejado de termos da sequencia de fibonacci: ");
  scanf("%d", &num);

  printf("0 \n");

  while(num > count){
    printf("%d \n", f);
    
    f += fant;
    fant = f - fant;
    
    count++;
  }

  return 0;
}