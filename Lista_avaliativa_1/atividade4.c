/*4. Implementar um algoritmo que solicita um número inteiro positivo N e mostre o enésimo termo da
sequência de Fibonacci. Essa sequência começa no termo de ordem zero e, a partir do segundo termo,
seu valor é dado pela soma dos dois termos anteriores. Exemplo: para N == 8, o enésimo termo é 13,
uma vez que a sequência de Fibonacci até o oitavo termo é: 0,1,1,2,3,5,8,13 */
#include<stdio.h>
#include<math.h>
int main(){
  int n, count = 2, f = 1, fant = 0;

  printf("Digite o enesimo (n) termo da sequencia de fibonacci: ");
  scanf("%d", &n);

  if(n == 0){
    printf("Termo invalido ");
    return 0;
  }
  else if(n == 1){
    printf("o enesimo termo eh o: 0 ");
    return 0;
  }

  while(n > count){
    f += fant;
    fant = f - fant;
    
    count++;
  }

  printf("o enesimo termo eh o: %d", f);
  return 0;
}