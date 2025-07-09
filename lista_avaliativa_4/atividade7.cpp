#include <iostream>
#include <string>
#include <stdexcept>

class SistemaLogin {
private:
    std::string usuario;
    std::string senha;
    const std::string USUARIO_VALIDO = "aluno";
    const std::string SENHA_VALIDA = "1234";

public:
    SistemaLogin() {}

    SistemaLogin(const std::string& usuario, const std::string& senha) {
        this->usuario = usuario;
        this->senha = senha;
    }

    bool logar(const std::string& usuario, const std::string& senha) {
        if (usuario.empty() || senha.empty()) {
            throw std::invalid_argument("Nome de usuario e senha nao podem ser vazios.");
        }
        
        if (usuario == USUARIO_VALIDO && senha == SENHA_VALIDA) {
            return true;
        } else {
            throw std::runtime_error("Acesso nao autorizado. Usuario ou senha incorretos.");
        }
    }
    
    bool logar() {
        return this->logar(this->usuario, this->senha);
    }
};

int main() {
    setlocale(LC_ALL, "Portuguese");

    SistemaLogin sistema;
    std::string usuarioInput;
    std::string senhaInput;

    std::cout << "--- Sistema de Login ---" << std::endl;
    std::cout << "Por favor, insira suas credenciais." << std::endl;
    
    std::cout << "Usuario: ";
    std::getline(std::cin, usuarioInput);

    std::cout << "Senha: ";
    std::getline(std::cin, senhaInput);

    try {
        if (sistema.logar(usuarioInput, senhaInput)) {
            std::cout << "\nLogin bem-sucedido! Acesso concedido." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "\nERRO: " << e.what() << std::endl;
    }

    // Exemplo demonstrando a sobrecarga com o construtor
    std::cout << "\n--- Testando a sobrecarga de metodo (login automatico) ---" << std::endl;
    SistemaLogin loginAutomatico("aluno", "1234");
    try {
        if(loginAutomatico.logar()){
            std::cout << "Login automatico bem-sucedido!" << std::endl;
        }
    } catch(const std::exception& e) {
        std::cerr << "ERRO no login automatico: " << e.what() << std::endl;
    }

    return 0;
}