#include "../algoritmos.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
 * Reducao Hamiltoniana por Heuristica Gulosa (Greedy).
 *
 * Procura um Caminho Hamiltoniano em grafos gerais usando estrategia gulosa:
 * em cada passo, entre os vizinhos nao visitados do vertice atual, escolhe
 * aquele que possui o maior grau de saida (adjacencias).
 *
 * Fundamentacao: um vertice com maior grau de saida oferece mais "rotas de
 * fuga" futuras, reduzindo drasticamente a chance de terminar num beco sem
 * saida. Executa em O(V + E).
 *
 * Estrategia: tenta multiplos pontos de partida (0 ate V-1) para aumentar
 * a chance de sucesso em grafos gerais.
 *
 * Pre-condicao: heuristica (pode falhar mesmo que exista Caminho Hamiltoniano).
 * Pos-condicao: retorna caminho como lista de arestas diretas; se falhar
 *              em todos os pontos de partida, retorna grafo original.
 */
vector<vector<int>> reducaoHamiltonianaGulosa(int V, const vector<vector<int>>& adj) {
    cout << "[GULOSO] Iniciando busca por Caminho Hamiltoniano com heuristica gulosa..." << endl;
    
    // Tenta cada vertice como ponto de partida
    for (int inicio = 0; inicio < V; inicio++) {
        cout << "   [TENTATIVA " << (inicio + 1) << "/" << V << "] Partindo do vertice " << inicio << endl;
        
        // Controle de visitacao
        vector<bool> visitado(V, false);
        vector<int> caminho;
        
        int atual = inicio;
        visitado[atual] = true;
        caminho.push_back(atual);
        
        // Constroi o caminho iterativamente
        bool sucesso = true;
        while ((int)caminho.size() < V) {
            // Encontra vizinho nao visitado com maior grau de saida
            int proximoVertice = -1;
            int maxGrau = -1;
            
            for (int vizinho : adj[atual]) {
                if (!visitado[vizinho]) {
                    int grau = adj[vizinho].size();
                    if (grau > maxGrau) {
                        maxGrau = grau;
                        proximoVertice = vizinho;
                    }
                }
            }
            
            // Se nao ha vizinho nao visitado, caminho bloqueado (beco sem saida)
            if (proximoVertice == -1) {
                cerr << "       [FALHA] Vertice " << atual << " nao tem vizinhos nao visitados. Visitados ate agora: "
                     << (int)caminho.size() << "/" << V << ". Retornando grafo original." << endl;
                return adj;
            }
            
            // Avanca para proximo vertice
            visitado[proximoVertice] = true;
            caminho.push_back(proximoVertice);
            cout << "       [SALTO] " << atual << " -> " << proximoVertice 
                 << " (grau saida: " << maxGrau << ")" << endl;
            atual = proximoVertice;
        }
        
        // Se conseguiu visitar todos os V vertices, retorna o caminho
        if (sucesso && (int)caminho.size() == V) {
            cout << "[GULOSO] SUCESSO! Caminho Hamiltoniano encontrado via tentativa " 
                 << (inicio + 1) << endl;
            cout << "   Sequencia: ";
            for (int i = 0; i < (int)caminho.size(); i++) {
                cout << caminho[i];
                if (i < (int)caminho.size() - 1) cout << " -> ";
            }
            cout << endl;
            
            // Constroi resultado: apenas arestas do caminho
            vector<vector<int>> resultado(V);
            for (int i = 0; i < (int)caminho.size() - 1; i++) {
                resultado[caminho[i]].push_back(caminho[i + 1]);
            }
            
            return resultado;
        }
    }
    
    // Se chegou aqui, nenhuma tentativa funcionou
    cerr << "[GULOSO] FALHA: nao foi possivel encontrar Caminho Hamiltoniano "
         << "em nenhum ponto de partida. Retornando grafo original." << endl;
    
    return adj;
}