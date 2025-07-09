#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <limits>

class ApostaLotofacil {
private:
    std::vector<int> numeros;
    static const int TAMANHO_MAXIMO_APOSTA = 15;
    static const int NUMERO_MINIMO = 1;
    static const int NUMERO_MAXIMO = 25;

public:
    ApostaLotofacil() {}

    void adicionarNumero(int numero) {
        if (numeros.size() >= TAMANHO_MAXIMO_APOSTA) {
            throw std::runtime_error("A aposta ja esta completa com 15 numeros.");
        }

        if (numero < NUMERO_MINIMO || numero > NUMERO_MAXIMO) {
            throw std::out_of_range("Numero invalido. Escolha um valor entre 1 e 25.");
        }

        if (std::find(numeros.begin(), numeros.end(), numero) != numeros.end()) {
            throw std::runtime_error("Numero repetido. Escolha outro valor.");
        }

        numeros.push_back(numero);
        std::sort(numeros.begin(), numeros.end());
    }

    void exibirAposta() const {
        std::cout << "\n--- Sua Aposta ---" << std::endl;
        for (int numero : numeros) {
            std::cout << numero << " ";
        }
        std::cout << "\n------------------" << std::endl;
    }
    
    int getQuantidadeNumeros() const {
        return numeros.size();
    }
};

int main() {
    setlocale(LC_ALL, "Portuguese");

    ApostaLotofacil minhaAposta;
    int numeroEscolhido;

    std::cout << "--- Aposta Lotofacil ---" << std::endl;
    std::cout << "Escolha 15 numeros de 1 a 25." << std::endl;

    while (minhaAposta.getQuantidadeNumeros() < 15) {
        minhaAposta.exibirAposta();
        std::cout << "Faltam " << 15 - minhaAposta.getQuantidadeNumeros() << " numeros." << std::endl;
        std::cout << "Digite um numero: ";
        std::cin >> numeroEscolhido;

        if (std::cin.fail()) {
            std::cerr << "ERRO: Entrada invalida. Por favor, digite um numero inteiro." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        try {
            minhaAposta.adicionarNumero(numeroEscolhido);
            std::cout << "Numero " << numeroEscolhido << " adicionado com sucesso!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    }
    
    std::cout << "\n*** Aposta finalizada com sucesso! ***" << std::endl;
    minhaAposta.exibirAposta();

    return 0;
}