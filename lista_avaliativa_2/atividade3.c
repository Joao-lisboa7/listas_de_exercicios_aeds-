#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
void preencheValores(int *vetorX, int *vetorY, int length){
  for(int i = 0; i < length; i++){
    vetorX[i] = (rand()%11) + 10;
    vetorY[i] = (rand()%11) + 10;
  }
}

void intercala(int *vetorX, int *vetorY, int length, int *vetorZ){
  for(int i = 0; i < length; i++){
    vetorZ[i * 2] = vetorX[i];
    vetorZ[i * 2 + 1] = vetorY[i];
  }
}

void mostraValores(int *vetorX, int *vetorY, int length, int *vetorZ){
  printf("vetorX: ");
  for(int i = 0; i < length; i++){
    printf("%d ", vetorX[i]);
  }

  printf(" vetorY: ");
  for(int i = 0; i < length; i++){
    printf("%d ", vetorY[i]);
  }

  printf("\n");
  printf("vetorZ: ");
  for(int i = 0; i < length * 2; i++){
    printf("%d ", vetorZ[i]);
  }
}

int main(){
  int length = 10;
  int vetorX[length], vetorY[length], vetorZ[20]; 
  srand(time(NULL));

  preencheValores(vetorX, vetorY, length);
  intercala(vetorX, vetorY, length, vetorZ);
  mostraValores(vetorX, vetorY, length, vetorZ);

  return 0;
}
