#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char modelo[100];
    char fabricante[100];
    float autonomia_km;
    float capacidade_tanque_litros;
} Carro;

void salvar_arquivo_binario(const char *nome_arquivo, Carro *carros, int qtd) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo binário.\n");
        return;
    }

    fwrite(carros, sizeof(Carro), qtd, arquivo);
    fclose(arquivo);
    printf("\nDados salvos em %s com sucesso!\n", nome_arquivo);
}

void visualizar_arquivo_binario(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo binário.\n");
        return;
    }

    Carro carro;
    printf("\nCarros armazenados no arquivo:\n");
    while (fread(&carro, sizeof(Carro), 1, arquivo)) {
        float km_por_litro = carro.autonomia_km / carro.capacidade_tanque_litros;
        printf("Modelo: %s | Fabricante: %s | Autonomia: %.2f km | Tanque: %.2f L | %.2f km/L\n",
               carro.modelo, carro.fabricante, carro.autonomia_km,
               carro.capacidade_tanque_litros, km_por_litro);
    }

    fclose(arquivo);
}

int main() {
    Carro carros[5];
    const char *nome_arquivo = "carros.bin";

    printf("Digite os dados de 5 carros:\n");
    for (int i = 0; i < 5; i++) {
        printf("\nCarro %d:\n", i + 1);
        printf("Modelo: ");
        scanf(" %[^\n]", carros[i].modelo);
        printf("Fabricante: ");
        scanf(" %[^\n]", carros[i].fabricante);
        printf("Autonomia (em km): ");
        scanf("%f", &carros[i].autonomia_km);
        printf("Capacidade do tanque (em litros): ");
        scanf("%f", &carros[i].capacidade_tanque_litros);
    }

    int melhor_idx = 0;
    float melhor_kml = carros[0].autonomia_km / carros[0].capacidade_tanque_litros;

    for (int i = 1; i < 5; i++) {
        float atual_kml = carros[i].autonomia_km / carros[i].capacidade_tanque_litros;
        if (atual_kml > melhor_kml) {
            melhor_kml = atual_kml;
            melhor_idx = i;
        }
    }

    printf("\nCarro com melhor quilometragem por litro:\n");
    printf("Modelo: %s | Fabricante: %s | %.2f km/L\n",
           carros[melhor_idx].modelo,
           carros[melhor_idx].fabricante,
           melhor_kml);

    salvar_arquivo_binario(nome_arquivo, carros, 5);

    char opcao;
    printf("\nDeseja visualizar os dados do arquivo binário? (s/n): ");
    scanf(" %c", &opcao);
    if (opcao == 's' || opcao == 'S') {
        visualizar_arquivo_binario(nome_arquivo);
    }

    return 0;
}
