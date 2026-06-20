#include "../algoritmos.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

const int MAX = 100; //Valor fixo em tempo de complicação para o bitset

static void dfsBitset(int u, const vector<vector<int>>& adj, vector<bitset<MAX>>& alcancado, vector<bool>& calculado){

    if(calculado[u]){
        return;
    }

    calculado[u] = true;
    alcancado[u].set(u);

    for(int v : adj[u]){
        dfsBitset(v, adj, alcancado, calculado);
        alcancado[u] |= alcancado[v];
    }
}

vector<vector<int>> reducaoTransitivaBitset(int V, const vector<vector<int>>& adj){

    vector<bitset<MAX>> alcancado(V);
    vector<bool> calculado(V, false);

    cout << "\n[LOG BITSET] Calculando matriz de atingibilidade usando operacoes bit a bit..." << endl;

    for(int i = 0; i < V; i++){
        if(!calculado[i]){
            dfsBitset(i, adj, alcancado, calculado);
        }
    }

    vector<vector<int>> reducaoAdj = adj;

    for(int i = 0; i < V; i++){
        for(int w : adj[i]){
            bool transitivo = false;

            for(int vizinho : adj[i]){
                if(vizinho != w && alcancado[vizinho].test(w)){
                    transitivo = true;
                    cout << "   -> [REMOVIDA] (" << i << " -> " << w << ") via Bitset. Vizinho " << vizinho << " possui o bit ativado." << endl;
                    break;
                }
            }

            if(transitivo){
                reducaoAdj[i].erase(remove(reducaoAdj[i].begin(), reducaoAdj[i].end(), w), reducaoAdj[i].end());
            }
        }
    }
    return reducaoAdj;
}
