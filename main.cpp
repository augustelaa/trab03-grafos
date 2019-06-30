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
    list<pair<int, int>> *adjacencia;

    public:
    void setOrdem(int ordem) {
        this->ordem = ordem;        
        this->adjacencia = new list<pair<int, int>>[ordem];
    }

    void adicionarArestaValorada(int verticeOrigem, int verticeDestino, int valor) {
        this->adjacencia[verticeOrigem].push_back(make_pair(verticeDestino, valor));
        this->adjacencia[verticeDestino].push_back(make_pair(verticeOrigem, valor));
    }

    int buscar(int subset[], int i) {
		if(subset[i] == -1)
			return i;
		return buscar(subset, subset[i]);
	}

    // função para unir dois subconjuntos em um único subconjunto
	void unir(int subset[], int v1, int v2) {
		int v1_set = buscar(subset, v1);
		int v2_set = buscar(subset, v2);
		subset[v1_set] = v2_set;
	}

    void kruskal() {

        // Ordenamos o vetor usando como base o peso (indice 2 da tupla)
        /*sort(this->adjacencia.begin(), this->adjacencia.end(),
            [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
				return (get<2>(a) < get<2>(b));
			});*/
        
        /*for (auto v : this->adjacencia) {
            cout << get<0>(v) << " " << get<1>(v) << " " << get<2>(v) << endl;
        }*/

        int *subset = new int[this->ordem];
        memset(subset, -1, sizeof(int) * this->ordem);
        int soma = 0;

        for(int i = 0; i < this->ordem; i++) {
            //cout << get<0>(this->adjacencia[i]) << " " << get<1>(this->adjacencia[i]) << " " << get<2>(this->adjacencia[i]) << endl;
            /*int v1 = buscar(subset, get<0>(this->adjacencia[i]));
            int v2 = buscar(subset, get<1>(this->adjacencia[i]));
            if (v1 != v2) {
                unir(subset, v1, v2);
                soma = soma + get<2>(this->adjacencia[i]);
            }*/
        }
        cout << "soma: " << soma;
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
    grafo4.setOrdem(4);
    grafo4.adicionarArestaValorada(0, 1, 10);
    grafo4.adicionarArestaValorada(0, 2, 5);
    grafo4.adicionarArestaValorada(0, 3, 10);
    grafo4.adicionarArestaValorada(1, 2, 3);
    grafo4.adicionarArestaValorada(1, 3, 4);
    grafo4.adicionarArestaValorada(2, 3, 2);
    grafo4.kruskal();

    Grafo grafo5;
    grafo5.setOrdem(4);
    grafo5.adicionarArestaValorada(0, 1, 1);
    grafo5.adicionarArestaValorada(0, 2, 1);
    grafo5.adicionarArestaValorada(0, 3, 1);
    grafo5.adicionarArestaValorada(1, 2, 3);
    grafo5.adicionarArestaValorada(1, 3, 4);
    grafo5.adicionarArestaValorada(2, 3, 2);
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