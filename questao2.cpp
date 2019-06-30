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

    void prim(int raiz) {
        list<pair<int, int>> fila; // Criamos a fila: (chave,vertice)
        int chave[this->ordem];

        int peso, infinito = std::numeric_limits<int>::max();
        // Preenche a fila com todos os vertices
        for (int i = 0; i < this->ordem; i ++) {
            peso = infinito; // peso sera infinito inicialmente
            if (i == raiz) { // Se for a raiz o peso é zero
                peso = 0;
            }
            fila.push_back(make_pair(peso, i));
            chave[i] = peso;
        }

        int predecessor[this->ordem]; // Vértice predecessor de v na árvore
        predecessor[raiz] = -1; // Nodo raiz não possui predecessor

        cout << endl << "Iniciou" << endl;
        pair<int,int> u;
        while(!fila.empty()) {
            //sort(fila.begin(), fila.end()); // ordenamos a fila pelas chaves
            fila.sort([](const pair<int,int>& a, const pair<int,int>& b){
                return a.first < b.first;
            });
            u = fila.front(); // pega o primeiro (menor custo)
            fila.pop_front(); // remove

            // Para cada adjacente do vertice removido:
            list<pair<int,int> >::iterator i;
            for (i = this->adjacencia[u.second].begin(); i != this->adjacencia[u.second].end(); i++) {
                //auto vAdj = find(fila.begin(), fila.end(), make_pair(infinito, i->first));

                auto vAdj = find_if(fila.begin(), fila.end(), [i](const pair<int,int>& a) {
                    return a.second == i->first;
                });


                if(vAdj != fila.end() && i->second < chave[i->first]) {
                    predecessor[i->first] = u.second;
                    chave[i->first] = i->second; // atualiza o vetor final
                    vAdj->first = i->second; // atualiza o item na fila
                }
            }
        }
        int soma = 0;
        for(int i = 0; i < this->ordem; i++) {
            soma = soma + chave[i];
        }
        cout << "Acabou, soma: " << soma;
        cout << endl;
    }

    void reiniciar() {
        this->adjacencia = new list<pair<int, int>>[ordem];
        this->ordem = 0;
    }
};


void importarArquivoLista(string arquivo) {
    string linha;
    int nLinha = 0, pos = 0, fim = 0, inicial = 0;
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
            } else if (nLinha == 1) {
                inicial = std::stoul(linha.substr(0, pos));
            }
            nLinha++;
            string linha2 = linha.substr(pos+1, sizeof(linha)+1);
            int pos2 = linha2.find(" ");
            grafo.adicionarArestaValorada(std::stoul(linha.substr(0, pos)), std::stoul(linha2.substr(0, pos2)), std::stoul(linha2.substr(pos2+1, sizeof(linha2)+1)));
            if (nLinha == (fim+1)) {
                fim = 0;
                nLinha = 0;
                grafo.prim(inicial);
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