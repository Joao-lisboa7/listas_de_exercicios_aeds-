#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int preencherVetor(int *vetor1){
  int j;
  for(int i = 0; i < 5; i++){
    printf("Digite o termo %d: ", i + 1);
    scanf("%d", &j);

    vetor1[i] = j;
  }
  return 0;
}

int newArray(int *vetor1, int *vetor2){
  for(int i = 0; i < 5; i++){
    vetor2[i] = vetor1[i] * 2;
  }

  return 0;
}

int main(){
  int vetor1[5], vetor2[5];

  preencherVetor(vetor1);
  newArray(vetor1, vetor2);

  printf("O segundo vetor eh: ");
  for(int i = 0; i < 5; i++){
   printf("%d ", vetor2[i]);
  }

  return 0;
}