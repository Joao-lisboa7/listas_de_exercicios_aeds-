#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <limits>

class ErroOperacao : public std::runtime_error {
public:
    ErroOperacao(const std::string& mensagem) : std::runtime_error(mensagem) {}
};

class ContaCorrente {
private:
    double saldo;

protected:
    void setSaldo(double novoSaldo) {
        saldo = novoSaldo;
    }

public:
    static constexpr double TAXA_OPERACAO = 0.005;

    ContaCorrente(double saldoInicial = 0.0) {
        if (saldoInicial < 0) {
            throw ErroOperacao("Saldo inicial nao pode ser negativo.");
        }
        saldo = saldoInicial;
    }

    virtual ~ContaCorrente() {}

    double getSaldo() const {
        return saldo;
    }

    void depositar(double quantia) {
        if (quantia <= 0) {
            throw ErroOperacao("Valor do deposito deve ser positivo.");
        }
        saldo += quantia;
    }

    virtual void sacar(double quantia) {
        if (quantia <= 0) {
            throw ErroOperacao("Valor do saque deve ser positivo.");
        }
        double taxa = quantia * TAXA_OPERACAO;
        if ((quantia + taxa) > saldo) {
            throw ErroOperacao("Saldo insuficiente para o saque e taxa.");
        }
        saldo -= (quantia + taxa);
    }
};

class ContaEspecial : public ContaCorrente {
public:
    static constexpr double TAXA_OPERACAO = 0.001;

    ContaEspecial(double saldoInicial = 0.0) : ContaCorrente(saldoInicial) {}

    void sacar(double quantia) override {
        if (quantia <= 0) {
            throw ErroOperacao("Valor do saque deve ser positivo.");
        }
        double taxa = quantia * TAXA_OPERACAO;
        if ((quantia + taxa) > getSaldo()) {
            throw ErroOperacao("Saldo insuficiente para o saque e taxa.");
        }
        setSaldo(getSaldo() - (quantia + taxa));
    }
};

void exibirMenu() {
    std::cout << "\n===== MENU =====" << std::endl;
    std::cout << "1. Depositar" << std::endl;
    std::cout << "2. Sacar" << std::endl;
    std::cout << "3. Exibir Saldo" << std::endl;
    std::cout << "4. Sair" << std::endl;
    std::cout << "Escolha uma opcao: ";
}

template<typename T>
T lerEntrada() {
    T valor;
    while (!(std::cin >> valor)) {
        std::cerr << "Entrada invalida. Por favor, tente novamente: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return valor;
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    ContaCorrente* conta = nullptr;

    try {
        std::cout << "--- Criacao de Conta ---" << std::endl;
        std::cout << "1. Conta Corrente Comum" << std::endl;
        std::cout << "2. Conta Corrente Especial" << std::endl;
        std::cout << "Digite o tipo de conta: ";
        int tipoConta = lerEntrada<int>();

        std::cout << "Digite o saldo inicial: R$ ";
        double saldoInicial = lerEntrada<double>();

        if (tipoConta == 2) {
            conta = new ContaEspecial(saldoInicial);
            std::cout << "\nConta Especial criada com sucesso!" << std::endl;
        } else {
            conta = new ContaCorrente(saldoInicial);
            std::cout << "\nConta Comum criada com sucesso!" << std::endl;
        }
    } catch (const ErroOperacao& e) {
        std::cerr << "\nERRO na criacao da conta: " << e.what() << std::endl;
        return 1;
    }

    int opcao;
    do {
        exibirMenu();
        opcao = lerEntrada<int>();

        try {
            switch (opcao) {
                case 1: {
                    std::cout << "Digite o valor do deposito: R$ ";
                    double valor = lerEntrada<double>();
                    conta->depositar(valor);
                    std::cout << "Deposito realizado com sucesso!" << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Digite o valor do saque: R$ ";
                    double valor = lerEntrada<double>();
                    conta->sacar(valor);
                    std::cout << "Saque realizado com sucesso!" << std::endl;
                    break;
                }
                case 3:
                    std::cout << std::fixed << std::setprecision(2);
                    std::cout << "Saldo atual: R$ " << conta->getSaldo() << std::endl;
                    break;
                case 4:
                    std::cout << "Encerrando o programa..." << std::endl;
                    break;
                default:
                    std::cout << "Opcao invalida. Tente novamente." << std::endl;
            }
        } catch (const ErroOperacao& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    } while (opcao != 4);

    delete conta;
    return 0;
}