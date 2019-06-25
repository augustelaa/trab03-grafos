#include <iostream>
#include <list>
#include <fstream>
#include <string>

using namespace std;

/**
 * Augusto Henrique da Conceição
 * Marcelo Luis Jung
 **/

class Grafo {
    protected:
    unsigned int ordem;
    unsigned int tamanho;
    list<pair<unsigned int, unsigned int>> *adjacencia;

    public:
    void setOrdem(unsigned int ordem) {
        this->ordem = ordem;
        this->tamanho = 0;
        this->adjacencia = new list<pair<unsigned int, unsigned int>>[ordem];
    }

    void setTamanho(unsigned int tamanho) {
        this->tamanho = tamanho;
    }

    void adicionarArestaValoradaNaoDirigida(unsigned int verticeOrigem, unsigned int verticeDestino, unsigned int valor) {
        this->adjacencia[verticeOrigem].push_back(make_pair(verticeDestino, valor));
        this->adjacencia[verticeDestino].push_back(make_pair(verticeOrigem, valor));
        this->tamanho++;
    }

    unsigned int obtemGrau(unsigned int vertice) {
        return this->adjacencia[vertice].size();
    }

    unsigned int getOrdem() {
        return ordem;
    }

    unsigned int getTamanho() {
        return tamanho;
    }
};

void importarArquivoLista(string arquivo, Grafo &grafo) {
    string linha;
    unsigned int nLinha = 0;
    ifstream arquivoEntrada;

    arquivoEntrada.open(arquivo);
    if (arquivoEntrada.is_open()) {
        while (getline(arquivoEntrada, linha)) {
            unsigned int pos = linha.find(" ");
            if (nLinha == 0) {
                grafo.setOrdem(std::stoul(linha.substr(0, pos))+2);
                nLinha++; 
                continue;
            }
            string linha2 = linha.substr(pos+1, sizeof(linha)+1);
            unsigned int pos2 = linha2.find(" ");
            grafo.adicionarArestaValoradaNaoDirigida(std::stoul(linha.substr(0, pos)), std::stoul(linha2.substr(0, pos2)), std::stoul(linha2.substr(pos2+1, sizeof(linha2)+1)));
        }
        arquivoEntrada.close();
    }
}

int main() {
    Grafo grafo;
    return 0;
}