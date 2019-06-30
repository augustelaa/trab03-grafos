

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
        sort(this->adjacencia.begin(), this->adjacencia.end(),
            [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
				return (get<2>(a) < get<2>(b));
			});
        
        /*for (auto v : this->adjacencia) {
            cout << get<0>(v) << " " << get<1>(v) << " " << get<2>(v) << endl;
        }*/

        int *subset = new int[this->ordem];
        memset(subset, -1, sizeof(int) * this->ordem);
        int soma = 0;

        for(int i = 0; i < this->ordem; i++) {
            //cout << get<0>(this->adjacencia[i]) << " " << get<1>(this->adjacencia[i]) << " " << get<2>(this->adjacencia[i]) << endl;
            int v1 = buscar(subset, get<0>(this->adjacencia[i]));
            int v2 = buscar(subset, get<1>(this->adjacencia[i]));
            if (v1 != v2) {
                unir(subset, v1, v2);
                soma = soma + get<2>(this->adjacencia[i]);
            }
        }
        cout << "soma: " << soma;
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


        pair<int,int> u;
        while(!fila.empty()) {
            //sort(fila.begin(), fila.end()); // ordenamos a fila pelas chaves
            fila.sort([](const pair<int,int>& a, const pair<int,int>& b){
                return a.first < b.first;
            });
            u = fila.front(); // pega o primeiro (menor custo)
            cout << "Processando " << u.second << endl;
            fila.pop_front(); // remove

            // Para cada adjacente do vertice removido:
            list<pair<int, int> >::iterator i;
            for (i = this->adjacencia[u.second].begin(); i != this->adjacencia[u.second].end(); i++) {
                cout << "Item: " << i->first << " - Peso: " << i->second;
                if(find(fila.begin(), fila.end(), make_pair(infinito, i->first)) != fila.end() && i->second < chave[i->first]) {
                    cout << " - Atualizando...";
                    predecessor[i->first] = u.second;
                    chave[i->first] = i->second;
                }
                cout << endl;
            }
        }
        cout << "Acabou";
        cout << endl;
    }    















void prim(int raiz) {
        list<int> fila; // Criamos a fila: (chave,vertice)
        int chave[this->ordem];

        int peso, infinito = std::numeric_limits<int>::max();
        // Preenche a fila com todos os vertices
        for (int i = 0; i < this->ordem; i ++) {
            peso = infinito; // peso sera infinito inicialmente
            if (i == raiz) { // Se for a raiz o peso é zero
                peso = 0;
            }
            fila.push_back(i);
            chave[i] = peso;
        }

        int predecessor[this->ordem]; // Vértice predecessor de v na árvore
        predecessor[raiz] = -1; // Nodo raiz não possui predecessor


        int u;
        while(!fila.empty()) {

            // ordenar chave
            sort(chave);

            // com base nos indices da chave ordenar a fila
            sort(fila,chave);
            
            u = fila.front(); // pega o primeiro (menor custo)
            cout << "Processando " << u << endl;
            fila.pop_front(); // remove

            // Para cada adjacente do vertice removido:
            list<pair<int, int> >::iterator i;
            for (i = this->adjacencia[u].begin(); i != this->adjacencia[u].end(); i++) {
                cout << "Item: " << i->first << " - Peso: " << i->second;
                if(find(fila.begin(), fila.end(), i->first) != fila.end() && i->second < chave[i->first]) {
                    cout << " - Atualizando...";
                    predecessor[i->first] = u;
                    chave[i->first] = i->second;
                }
                cout << endl;
            }
        }
        cout << "Acabou";
        cout << endl;
    }    