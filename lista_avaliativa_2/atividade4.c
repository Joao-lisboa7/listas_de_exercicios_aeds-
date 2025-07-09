#include <stdio.h>
#include <ctype.h>
#include <string.h>
int validaSenha(char senha[]) {
    int temMaiuscula = 0, temMinuscula = 0, temNumero = 0, temEspecial = 0;
    int tamanho = strlen(senha);

    if (tamanho < 8) {
        return 0;
    }
  
    for (int i = 0; i < tamanho; i++) {
        if (isupper(senha[i])) temMaiuscula = 1;
        else if (islower(senha[i])) temMinuscula = 1;
        else if (isdigit(senha[i])) temNumero = 1;
        else temEspecial = 1;
    }

    return temMaiuscula && temMinuscula && temNumero && temEspecial;
}
  
void pedeSenha(char senha[]) {
    printf("A senha deve ter no minimo 8 caracteres, incluindo letra maiuscula, minuscula, numero e caractere especial.\nCrie uma senha: ");
    fgets(senha, 100, stdin);
 
    size_t len = strlen(senha);
    if (len > 0 && senha[len - 1] == '\n') {
        senha[len - 1] = '\0';
    }
}
         
void mostraResultado(int valida) {
    if (valida) {
        printf("Senha valida!\n");
    } else {
        printf("Senha invalida.\n");
    }
}

int main() {
    char senha[100];
 
    pedeSenha(senha);
    int resultado = validaSenha(senha);
    mostraResultado(resultado);
        
    return 0;
}