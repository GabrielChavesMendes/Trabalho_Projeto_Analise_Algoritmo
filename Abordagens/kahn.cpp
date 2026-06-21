#include "../algoritmos.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> reducaoKahn(int V, const vector<vector<int>>& adj){

    cout << "\n[LOG KAHN] Passo 1: Calculando Graus de Entrada (In-Degress)..." << endl;

    vector<int> grauEntrada(V, 0);

    for(int i = 0; i < V; i++){
        for(int v : adj[i]){
            grauEntrada[v]++;
        }
    }

    queue<int> fila;

    for(int i = 0; i < V; i++){
        if(grauEntrada[i] == 0){
            fila.push(i);
        }
    }

    vector<int> ordemTopologica;

    while(!fila.empty()){
        int u = fila.front();
        fila.pop();
        ordemTopologica.push_back(u);

        for(int v : adj[u]){
            grauEntrada[v]--;

            if(grauEntrada[v] == 0){
                fila.push(v);
            }
        }
    }

    cout << "[LOG KAHN] Ordem Topologica encontrada (pais para filhos): ";

    for(int v : ordemTopologica){
        cout << v << " ";
    }

    cout << "\n[LOG KAHN] Passo 2: Processando reducao herdando caminhos de tras para frente..." << endl;

    vector<vector<bool>> alcancado(V, vector<bool>(V, false));
    vector<vector<int>> reducaoAdj = adj;

    for(int i = V - 1; i >= 0; i--){
        int u = ordemTopologica[i];

        for(int w : adj[u]){
            bool transitivo = false;

            for(int vizinho : adj[u]){
                if(vizinho != w && alcancado[vizinho][w]){
                    transitivo = true;
                    cout << "   -> [REMOVIDA] (" << u << " -> " << w << "). Atalho encontrado via " << vizinho << "." << endl;
                    break;
                }
            }

            if(transitivo){
                reducaoAdj[u].erase(remove(reducaoAdj[u].begin(), reducaoAdj[u].end(), w), reducaoAdj[u].end());
            }
        }

        for(int v : reducaoAdj[u]){
            alcancado[u][v] = true;

            for(int w = 0; w < V; w++){
                if(alcancado[v][w]){
                    alcancado[u][w] = true;
                }
            }
        }
    }
    return reducaoAdj;
}
