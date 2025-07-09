//6. Escreva um programa que apresente o menu de opções a seguir e permita ao usuário escolher a
//opção desejada. Leia os dados necessários para executar a operação e mostre o resultado. Esse
//processo deverá ser repetido até que o usuário escolha a opção 4.
#include<stdio.h>
#include<math.h>
int main(){
  int opcao, meses;
  float salario, ferias, aumento, decimoTerceiro;
  
  do{
    printf("            MENU DE OPCOES            \n");
    printf("======================================\n");
    printf(" 1 - Novo Salario\n");
    printf(" 2 - Ferias\n");
    printf(" 3 - Decimo terceiro\n");
    printf(" 4 - Sair\n");
    printf("======================================\n");
  
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao){
    case 1:
      printf("Digite seu salario: ");
      scanf("%f", &salario);

      if(salario < 1000){
        aumento = salario * 0.15;
      }else if(salario >= 1000 && salario <= 2000){
        aumento = salario * 0.10;
      }else{
        aumento = salario * 0.05;
      }

      salario += aumento;
      printf("Novo salario: %.2fR$ \n", salario);
    break;
    
    case 2:
      printf("Digite seu salario: ");
      scanf("%f", &salario);

      ferias = salario + (0.33333 * salario);
      printf("Ferias: %.2fR$ \n", ferias);
    break;
    
    case 3:
      printf("Digite seu salario: ");
      scanf("%f", &salario);
      printf("Voce tem quantos meses de trabalho (de 1 a 12): ");
      scanf("%d", &meses);

      if(meses >= 1 && meses <= 12){
        decimoTerceiro = (salario * meses) / 12.0;
        printf("Decimo terceiro: %.2fR$ \n", decimoTerceiro);
      }else{
        printf("Quantidade de meses invaladia \n");
      }
    break;

    case 4:
      printf("Saiu");
    break;

    default:
      printf("Opcao invalida: \n");
      break;
    }
  }while(opcao != 4);

  return 0;
}