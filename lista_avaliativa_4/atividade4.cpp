#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>

class ErroCadastro : public std::runtime_error {
public:
    ErroCadastro(const std::string& mensagem) : std::runtime_error(mensagem) {}
};

class Animal {
private:
    std::string nome;
    std::string raca;
    int idade;
    double preco;

public:
    Animal(std::string nome, std::string raca, int idade, double preco) {
        if (nome.empty() || raca.empty()) {
            throw ErroCadastro("Nome e raca nao podem ser vazios.");
        }
        if (idade < 0 || preco < 0.0) {
            throw ErroCadastro("Idade e preco nao podem ser negativos.");
        }
        this->nome = nome;
        this->raca = raca;
        this->idade = idade;
        this->preco = preco;
    }

    virtual ~Animal() {}

    std::string getNome() const { return nome; }
    void setNome(std::string nome) { this->nome = nome; }

    std::string getRaca() const { return raca; }
    void setRaca(std::string raca) { this->raca = raca; }

    int getIdade() const { return idade; }
    void setIdade(int idade) {
        if (idade < 0) throw ErroCadastro("Idade nao pode ser negativa.");
        this->idade = idade;
    }

    double getPreco() const { return preco; }
    void setPreco(double preco) {
        if (preco < 0.0) throw ErroCadastro("Preco nao pode ser negativo.");
        this->preco = preco;
    }

    virtual void exibirDetalhes() const {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Nome: " << nome << " | Raca: " << raca << " | Idade: " << idade << " | Preco: R$ " << preco;
    }
};

class Cachorro : public Animal {
public:
    Cachorro(std::string nome, std::string raca, int idade, double preco)
        : Animal(nome, raca, idade, preco) {}

    void exibirDetalhes() const override {
        std::cout << "[Cachorro] ";
        Animal::exibirDetalhes();
        std::cout << std::endl;
    }
};

class Gato : public Animal {
public:
    Gato(std::string nome, std::string raca, int idade, double preco)
        : Animal(nome, raca, idade, preco) {}

    void exibirDetalhes() const override {
        std::cout << "[Gato]     ";
        Animal::exibirDetalhes();
        std::cout << std::endl;
    }
};

class Loja {
private:
    std::vector<Animal*> animais;

public:
    ~Loja() {
        for (Animal* animal : animais) {
            delete animal;
        }
        animais.clear();
    }

    void adicionarAnimal(Animal* animal) {
        for (const auto& existente : animais) {
            if (existente->getNome() == animal->getNome()) {
                delete animal;
                throw ErroCadastro("Ja existe um animal com este nome.");
            }
        }
        animais.push_back(animal);
    }

    void listarAnimais() const {
        std::cout << "\n--- LISTA DE ANIMAIS NA LOJA ---" << std::endl;
        if (animais.empty()) {
            std::cout << "Nenhum animal cadastrado." << std::endl;
        } else {
            for (const Animal* animal : animais) {
                animal->exibirDetalhes();
            }
        }
        std::cout << "------------------------------------" << std::endl;
    }

    Animal* buscarAnimal(const std::string& nome) {
        for (Animal* animal : animais) {
            if (animal->getNome() == nome) {
                return animal;
            }
        }
        throw ErroCadastro("Animal nao encontrado.");
    }

    void removerAnimal(const std::string& nome) {
        for (auto it = animais.begin(); it != animais.end(); ++it) {
            if ((*it)->getNome() == nome) {
                delete *it;
                animais.erase(it);
                return;
            }
        }
        throw ErroCadastro("Animal nao encontrado para remocao.");
    }
};

template<typename T>
T lerEntradaNumerica(const std::string& prompt) {
    T valor;
    std::cout << prompt;
    while (!(std::cin >> valor)) {
        std::cerr << "Entrada invalida. Tente novamente: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valor;
}

void exibirMenu() {
    std::cout << "\n===== PET SHOP MANAGER =====" << std::endl;
    std::cout << "1. Adicionar Animal" << std::endl;
    std::cout << "2. Listar Animais" << std::endl;
    std::cout << "3. Atualizar Animal" << std::endl;
    std::cout << "4. Vender/Remover Animal" << std::endl;
    std::cout << "5. Sair" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    Loja petShop;
    int opcao = 0;

    do {
        exibirMenu();
        opcao = lerEntradaNumerica<int>("Escolha uma opcao: ");

        try {
            switch (opcao) {
                case 1: {
                    int tipo = lerEntradaNumerica<int>("Qual tipo de animal? (1-Cachorro, 2-Gato): ");
                    if (tipo != 1 && tipo != 2) {
                        throw ErroCadastro("Tipo de animal invalido.");
                    }

                    std::string nome, raca;
                    std::cout << "Nome: ";
                    std::getline(std::cin, nome);
                    std::cout << "Raca: ";
                    std::getline(std::cin, raca);

                    int idade = lerEntradaNumerica<int>("Idade: ");
                    double preco = lerEntradaNumerica<double>("Preco: R$ ");
                    
                    Animal* novoAnimal = nullptr;
                    if (tipo == 1) {
                        novoAnimal = new Cachorro(nome, raca, idade, preco);
                    } else {
                        novoAnimal = new Gato(nome, raca, idade, preco);
                    }
                    petShop.adicionarAnimal(novoAnimal);
                    std::cout << "Animal adicionado com sucesso!" << std::endl;
                    break;
                }
                case 2: {
                    petShop.listarAnimais();
                    break;
                }
                case 3: {
                    std::string nome;
                    std::cout << "Digite o nome do animal para atualizar: ";
                    std::getline(std::cin, nome);
                    
                    Animal* animal = petShop.buscarAnimal(nome);
                    
                    std::cout << "--- Atualizando " << animal->getNome() << " ---" << std::endl;
                    std::string novaRaca;
                    std::cout << "Nova Raca: ";
                    std::getline(std::cin, novaRaca);
                    if(!novaRaca.empty()) animal->setRaca(novaRaca);

                    int novaIdade = lerEntradaNumerica<int>("Nova Idade: ");
                    animal->setIdade(novaIdade);

                    double novoPreco = lerEntradaNumerica<double>("Novo Preco: R$ ");
                    animal->setPreco(novoPreco);

                    std::cout << "Animal atualizado com sucesso!" << std::endl;
                    break;
                }
                case 4: {
                    std::string nome;
                    std::cout << "Digite o nome do animal a ser vendido/removido: ";
                    std::getline(std::cin, nome);
                    petShop.removerAnimal(nome);
                    std::cout << "Animal removido com sucesso." << std::endl;
                    break;
                }
                case 5: {
                    std::cout << "Encerrando o programa..." << std::endl;
                    break;
                }
                default: {
                    std::cout << "Opcao invalida. Tente novamente." << std::endl;
                }
            }
        } catch (const ErroCadastro& e) {
            std::cerr << "ERRO: " << e.what() << std::endl;
        }
    } while (opcao != 5);

    return 0;
}