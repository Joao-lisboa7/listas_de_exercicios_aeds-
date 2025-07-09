#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include <iomanip>

using namespace std;

class ErroRegistro : public runtime_error {
public:
    ErroRegistro(const string& mensagem) : runtime_error(mensagem) {}
};

class RegistraPreco {
private:
    string nome_da_loja;
    int telefone;
    string alimento;
    float preco;

public:
    RegistraPreco(string nome_da_loja, int telefone, string alimento, float preco) {
        if (nome_da_loja.empty() || alimento.empty()) {
            throw ErroRegistro("Nome da loja e do alimento nao podem ser vazios.");
        }
        if (preco < 0) {
            throw ErroRegistro("Preco nao pode ser um valor negativo.");
        }
        this->nome_da_loja = nome_da_loja;
        this->telefone = telefone;
        this->alimento = alimento;
        this->preco = preco;
    }

    void imprime_dados() const {
        cout << fixed << setprecision(2);
        cout << "Loja: " << nome_da_loja << " (" << telefone << ")" << endl;
        cout << "  - Alimento: " << alimento << " | Preco: R$ " << preco << endl;
    }

    float getPreco() const {
        return preco;
    }
};

int main() {
    setlocale(LC_ALL, "Portuguese");

    vector<RegistraPreco> lista;
    int quant = 0;

    cout << "Quantos registros de preco deseja fazer? ";
    cin >> quant;

    if (cin.fail() || quant <= 0) {
        cerr << "Quantidade invalida. Encerrando." << endl;
        return 1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < quant; i++) {
        try {
            cout << "\n--- Registro #" << i + 1 << " ---" << endl;
            string nome_da_loja;
            int telefone;
            string alimento;
            float preco;

            cout << "Nome da loja: ";
            getline(cin, nome_da_loja);

            cout << "Telefone: ";
            cin >> telefone;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw ErroRegistro("Telefone deve ser um valor numerico.");
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Alimento: ";
            getline(cin, alimento);

            cout << "Preco: R$ ";
            cin >> preco;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw ErroRegistro("Preco deve ser um valor numerico.");
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            lista.push_back(RegistraPreco(nome_da_loja, telefone, alimento, preco));
            cout << "Registro adicionado com sucesso!" << endl;
        } catch (const ErroRegistro& e) {
            cerr << "Erro no registro: " << e.what() << " Tente novamente." << endl;
            i--;
        }
    }

    if (lista.empty()) {
        cout << "\nNenhum registro foi feito." << endl;
        return 0;
    }

    cout << "\n--- Dados Registrados ---" << endl;
    for (const auto& item : lista) {
        item.imprime_dados();
    }

    float menor_preco = lista[0].getPreco();
    float maior_preco = lista[0].getPreco();
    float soma = 0.0f;

    for (const auto& item : lista) {
        float preco_atual = item.getPreco();
        soma += preco_atual;
        if (preco_atual < menor_preco) {
            menor_preco = preco_atual;
        }
        if (preco_atual > maior_preco) {
            maior_preco = preco_atual;
        }
    }

    float media = soma / lista.size();

    cout << "\n--- Resumo dos Precos ---" << endl;
    cout << fixed << setprecision(2);
    cout << "Menor preco: R$ " << menor_preco << endl;
    cout << "Maior preco: R$ " << maior_preco << endl;
    cout << "Media dos precos: R$ " << media << endl;

    return 0;
}