#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

class ErroCadastro : public runtime_error {
public:
    ErroCadastro(const string& mensagem) : runtime_error(mensagem) {}
};

class Cliente {
private:
    string nome;
    string endereco;
    string nascimento;
    int telefone;

public:
    Cliente(const string& nome, const string& endereco, const string& nascimento, int telefone);

    string getNome() const { return nome; }
    string getEndereco() const { return endereco; }
    string getNascimento() const { return nascimento; }
    int getTelefone() const { return telefone; }
};

Cliente::Cliente(const string& nome, const string& endereco, const string& nascimento, int telefone) {
    if (nome.empty() || endereco.empty() || nascimento.empty()) {
        throw ErroCadastro("Erro: Nome, endereco e data de nascimento nao podem ser vazios.");
    }
    if (telefone <= 0) {
        throw ErroCadastro("Erro: O numero de telefone informado e invalido.");
    }

    this->nome = nome;
    this->endereco = endereco;
    this->nascimento = nascimento;
    this->telefone = telefone;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    vector<Cliente*> clientes;
    int quant = 0;

    cout << "Quantos clientes voce quer cadastrar: ";
    cin >> quant;

    if (cin.fail() || quant <= 0) {
        cerr << "Quantidade invalida. O programa sera encerrado." << endl;
        return 1;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < quant; i++) {
        try {
            cout << "\n--- Cadastro do Cliente " << i + 1 << " ---" << endl;
            
            string nome, endereco, nascimento;
            int telefone;

            cout << "Digite o nome: ";
            getline(cin, nome);

            cout << "Digite o endereco: ";
            getline(cin, endereco);

            cout << "Digite a sua data de nascimento: ";
            getline(cin, nascimento);

            cout << "Digite o numero de telefone: ";
            cin >> telefone;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw ErroCadastro("Erro: Telefone deve ser um numero.");
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            Cliente* c = new Cliente(nome, endereco, nascimento, telefone);
            clientes.push_back(c);
            cout << "Cliente cadastrado com sucesso!" << endl;

        } catch (const ErroCadastro& e) {
            cerr << "Nao foi possivel cadastrar o cliente. Motivo: " << e.what() << endl;
            i--;
        }
    }

    if (!clientes.empty()) {
        cout << "\n========= Exibicao de Clientes Cadastrados =========\n";
        for (size_t i = 0; i < clientes.size(); i++) {
            cout << "\n--- Cliente: " << i + 1 << " ---\n";
            cout << "Nome: " << clientes[i]->getNome() << endl;
            cout << "Endereco: " << clientes[i]->getEndereco() << endl;
            cout << "Data de nascimento: " << clientes[i]->getNascimento() << endl;
            cout << "Telefone: " << clientes[i]->getTelefone() << endl;
        }
    }

    for (size_t i = 0; i < clientes.size(); i++) {
        delete clientes[i];
    }
    
    return 0;
}