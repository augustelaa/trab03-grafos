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
        this->ordem = ordem;        
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
};

/*void importarArquivoLista(string arquivo, Grafo &grafo) {
    string linha;
    int nLinha = 0;
    ifstream arquivoEntrada;

    arquivoEntrada.open(arquivo);
    if (arquivoEntrada.is_open()) {
        while (getline(arquivoEntrada, linha)) {
            int pos = linha.find(" ");
            if (nLinha == 0) {
                grafo.setOrdem(std::stoul(linha.substr(0, pos))+2);
                nLinha++; 
                continue;
            }
            string linha2 = linha.substr(pos+1, sizeof(linha)+1);
            int pos2 = linha2.find(" ");
            grafo.adicionarArestaValorada(std::stoul(linha.substr(0, pos)), std::stoul(linha2.substr(0, pos2)), std::stoul(linha2.substr(pos2+1, sizeof(linha2)+1)));
        }
        arquivoEntrada.close();
    }
}*/

int main() {

    Grafo grafo4;
    grafo4.setOrdem(6);
    grafo4.adicionarArestaValorada(1, 2, 15);
    grafo4.adicionarArestaValorada(1, 3, 10);
    grafo4.adicionarArestaValorada(2, 3, 1);
    grafo4.adicionarArestaValorada(3, 4, 3);
    grafo4.adicionarArestaValorada(2, 4, 5);
    grafo4.adicionarArestaValorada(4, 5, 20);
    grafo4.kruskal();

    Grafo grafo5;
    grafo5.setOrdem(5);
    grafo5.adicionarArestaValorada(1, 2, 1);
    grafo5.adicionarArestaValorada(1, 3, 10);
    grafo5.adicionarArestaValorada(1, 4, 1);
    grafo5.adicionarArestaValorada(2, 3, 1);
    grafo5.adicionarArestaValorada(2, 4, 10);
    grafo5.adicionarArestaValorada(3, 4, 1);
    grafo5.kruskal();

    Grafo grafo6;
    grafo6.setOrdem(9);
    grafo6.adicionarArestaValorada(0, 1, 4);
    grafo6.adicionarArestaValorada(0, 7, 8);
    grafo6.adicionarArestaValorada(1, 2, 8);
    grafo6.adicionarArestaValorada(1, 7, 11);
    grafo6.adicionarArestaValorada(2, 3, 7);
    grafo6.adicionarArestaValorada(2, 5, 4);
    grafo6.adicionarArestaValorada(2, 8, 2);
    grafo6.adicionarArestaValorada(3, 4, 9);
    grafo6.adicionarArestaValorada(3, 5, 14);
    grafo6.adicionarArestaValorada(4, 5, 10);
    grafo6.adicionarArestaValorada(5, 6, 2);
    grafo6.adicionarArestaValorada(6, 8, 6);
    grafo6.adicionarArestaValorada(6, 7, 1);
    grafo6.adicionarArestaValorada(7, 8, 7);
    grafo6.kruskal();

    return 0;
}