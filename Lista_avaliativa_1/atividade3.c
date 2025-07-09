/* 3.Implementar um algoritmo que recebe solicita ao usuário um número inteiro N e mostra a soma de
todos os números positivos menores ou iguais a N que são divisíveis por 3 ou por 5, mas não por
ambos */
#include<stdio.h>
/* 3.Implementar um algoritmo que recebe solicita ao usuário um número inteiro N e mostra a soma de
todos os números positivos menores ou iguais a N que são divisíveis por 3 ou por 5, mas não por
ambos. Exemplo: para N==20, a soma é 3+5+6+9+10+12+18+20 = 83 */
#include<math.h>
int main(){
  int num, soma = 0;

  printf("Digite um numero: ");
  scanf("%d", &num);

  do{
    if(num % 3 == 0 && num % 5 != 0){
      soma += num;
    }
    if(num % 5 == 0 && num % 3 != 0){
      soma += num;
    }

    num--;
  }while(num > 0);

printf("%d", soma);

  return 0;
}