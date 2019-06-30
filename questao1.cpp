#include <iostream>
#include <list>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

/**
 * Augusto Henrique da Conceição
 * Marcelo Luis Jung
 **/

class Grafo {
    protected:
    int ordem;
    // Para este exercicio usaremos uma lista de tuplas ao inves da boa e velha matriz de lista de pares
    // Isso será feito por facilidades na ordenação, busca e etc.
    list<tuple<int, int, int>> adjacencia; // origem, destino, peso

    public:
    void setOrdem(int ordem) {
        this->ordem = ordem+1;        
    }

    void adicionarArestaValorada(int verticeOrigem, int verticeDestino, int valor) {
        this->adjacencia.push_back(make_tuple(verticeOrigem, verticeDestino, valor));
    }

    // FIND-SET
    int buscar(list<int> *subset, int v) {
		for (int i = 0; i < this->ordem; i ++) {
            if (find(subset[i].begin(), subset[i].end(), v) != subset[i].end()) {
                return i;
            }
        }
        return -1;
	}

    // UNION
	void unir(list<int> *subset, int setA, int setB) {
        do {
		    subset[setA].push_back(subset[setB].front());
            subset[setB].pop_front();
        } while(!subset[setB].empty());
	}

    void kruskal() {
        list<int> *subset = new list<int>[this->ordem];
        // MAKE-SET
        for (int i = 0; i < this->ordem; i ++) {
            subset[i].push_back(i);
        }

        // Ordena a lista pelo peso
        this->adjacencia.sort([](const tuple<int,int,int>& a, const tuple<int,int,int>& b){
            return get<2>(a) < get<2>(b);
        });

        int soma = 0;
        cout << endl << "Iniciou" << endl;
       
        // Para cada adjacencia ordenada
        list<tuple<int,int,int>>::iterator i;
        for (i = this->adjacencia.begin(); i != this->adjacencia.end(); i++) {
            int setA = buscar(subset, get<0>(*i)); // busca o SET da origem
            int setB = buscar(subset, get<1>(*i)); // buscar o SET do destino
            if (setA != setB) { // Se forem diferentes
                unir(subset, setA, setB); // Realiza a uniao dos SET
                soma = soma + get<2>(*i); // Soma o peso total construido
            }
        }
        cout << "Acabou, soma: " << soma << endl;
    }

    void reiniciar() {
        this->adjacencia.clear();
        this->ordem = 0;
    }
};

void importarArquivoLista(string arquivo) {
    string linha;
    int nLinha = 0, pos = 0, fim = 0;
    ifstream arquivoEntrada;
    Grafo grafo;

    arquivoEntrada.open(arquivo);
    if (arquivoEntrada.is_open()) {
        while (getline(arquivoEntrada, linha)) {
            pos = linha.find(" ");
            if (nLinha == 0) {
                grafo.setOrdem(std::stoul(linha.substr(0, pos)));
                fim = std::stoul(linha.substr(pos, sizeof(linha)+1));
                nLinha++; 
                continue;
            }
            nLinha++;
            string linha2 = linha.substr(pos+1, sizeof(linha)+1);
            int pos2 = linha2.find(" ");
            grafo.adicionarArestaValorada(std::stoul(linha.substr(0, pos)), std::stoul(linha2.substr(0, pos2)), std::stoul(linha2.substr(pos2+1, sizeof(linha2)+1)));
            if (nLinha == (fim+1)) {
                fim = 0;
                nLinha = 0;
                grafo.kruskal();
                grafo.reiniciar();
            }
        }
        arquivoEntrada.close();
    }
}

int main() {

    importarArquivoLista("c:/temp/entrada.in");

    return 0;
}