#include<stdio.h>
#include<math.h>
#include<stdlib.h>
void preencheNotas(int tam, int vetor[]){
  int j;

  for(int i = 0; i < tam; i++){
    printf("Digite o termo %d: ", i);
    scanf("%d", &j);

    vetor[i] = j;
  }
}
void calculaMedia(int tam, int vetor[]){
  int soma = 0, media, quantAlunos = 0;

  for(int i = 0; i < tam; i++){
    soma += vetor[i];
  }

  media = soma / tam;
  
  
  for(int i = 0; i < tam; i++){
    if(vetor[i] >= media){
      quantAlunos++;
    }
  }

  printf("A media da turma foi de: %d\n", media);
  printf("A quantidade de alunos que ficaram na media ou acima dela eh: %d", quantAlunos);
}

int main(){
  int tam = 10, vetor[tam];

  preencheNotas(tam, vetor);
  calculaMedia(tam, vetor);

  return 0;
}