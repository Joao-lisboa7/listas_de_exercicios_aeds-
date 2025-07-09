#include <iostream>
#include <vector>

void preencherVetor(std::vector<int> & vetor1){
    int j;
    for (size_t i = 0; i < vetor1.size(); i++) {
        std::cout << "Digite o termo " << i + 1 << ": ";
        std::cin >> j;
        vetor1[i] = j;
    }
}

void newArray(const std::vector<int>& vetor1, std::vector<int>& vetor2){
    for (size_t i = 0; i < vetor1.size(); i++) {
        vetor2[i] = vetor1[i] * 2;
    }
}

int main(){
    std::vector<int> vetor1(5);
    std::vector<int> vetor2(5);

    preencherVetor(vetor1);
    newArray(vetor1, vetor2);

    std::cout << "O segundo vetor eh: ";
    for (int val : vetor2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}