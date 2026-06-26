#include "../algoritmos.h"
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

// Verifica se o grafo e um torneio valido:
// para todo par (u,v), existe exatamente uma aresta entre eles
static bool ehTorneio(int V, const vector<vector<int>>& adj) {
    // Monta conjunto de arestas para consulta rapida
    vector<vector<bool>> temAresta(V, vector<bool>(V, false));
    for (int u = 0; u < V; u++)
        for (int v : adj[u])
            temAresta[u][v] = true;

    for (int u = 0; u < V; u++) {
        for (int v = u + 1; v < V; v++) {
            bool uParaV = temAresta[u][v];
            bool vParaU = temAresta[v][u];

            // Deve existir exatamente uma das duas direcoes
            if (uParaV == vParaU) {
                if (uParaV)
                    cerr << "[Redei] ERRO: Par (" << u << "," << v
                         << ") tem aresta nas duas direcoes (nao e torneio)." << endl;
                else
                    cerr << "[Redei] ERRO: Par (" << u << "," << v
                         << ") nao tem nenhuma aresta (nao e torneio)." << endl;
                return false;
            }
        }
    }
    return true;
}

// Verifica se a atingibilidade de 'src' e identica em adj e resultado
// usando DFS simples
static void dfsAtingibilidade(int u, const vector<vector<int>>& adj,
                               vector<bool>& visitado) {
    visitado[u] = true;
    for (int v : adj[u])
        if (!visitado[v])
            dfsAtingibilidade(v, adj, visitado);
}

static bool verificaAtingibilidade(int V,
                                    const vector<vector<int>>& original,
                                    const vector<vector<int>>& resultado) {
    for (int src = 0; src < V; src++) {
        vector<bool> alcOrig(V, false), alcRes(V, false);
        dfsAtingibilidade(src, original, alcOrig);
        dfsAtingibilidade(src, resultado, alcRes);

        for (int dst = 0; dst < V; dst++) {
            if (dst == src) continue;
            if (alcOrig[dst] != alcRes[dst]) {
                cerr << "[Redei] AVISO: Atingibilidade perdida: "
                     << src << " -> " << dst << endl;
                return false;
            }
        }
    }
    return true;
}

/*
 * Teorema de Redei: Todo torneio possui pelo menos um Caminho Hamiltoniano.
 * Constroi o caminho inserindo vertices um a um na posicao correta — O(V^2).
 *
 * Pre-condicao: o grafo deve ser um torneio (digrafo completo sem ciclos de 2).
 * Pos-condicao: preserva a mesma atingibilidade do grafo original.
 */
vector<vector<int>> reducaoHamiltonianaRedei(int V, const vector<vector<int>>& adj) {
    // --- Validacao de pre-condicao ---
    if (!ehTorneio(V, adj)) {
        cerr << "[Redei] Grafo invalido: nao e um torneio. "
             << "Retornando grafo vazio." << endl;
        return vector<vector<int>>(V);
    }

    // Monta matriz de adjacencia para consulta O(1) durante a insercao
    vector<vector<bool>> temAresta(V, vector<bool>(V, false));
    for (int u = 0; u < V; u++)
        for (int v : adj[u])
            temAresta[u][v] = true;

    // --- Algoritmo de Redei: insercao incremental ---
    list<int> caminho;

    for (int v = 0; v < V; v++) {
        if (caminho.empty()) {
            caminho.push_back(v);
            continue;
        }

        // v ganha do primeiro elemento → insere no inicio
        if (temAresta[v][caminho.front()]) {
            caminho.push_front(v);
            continue;
        }

        // Percorre o caminho procurando posicao de insercao no meio:
        // condicao: *it → v e v → *proximo
        bool inserido = false;
        for (auto it = caminho.begin(); it != caminho.end(); ++it) {
            auto proximo = next(it);
            if (proximo == caminho.end()) break;

            if (temAresta[*it][v] && temAresta[v][*proximo]) {
                caminho.insert(proximo, v);
                inserido = true;
                break;
            }
        }

        // Nao encontrou posicao no meio → v perde para todos → vai ao fim
        if (!inserido)
            caminho.push_back(v);
    }

    // --- Monta lista de adjacencia com as arestas do caminho encontrado ---
    vector<int> ordem(caminho.begin(), caminho.end());
    vector<vector<int>> resultado(V);

    for (int i = 0; i + 1 < (int)ordem.size(); i++)
        resultado[ordem[i]].push_back(ordem[i + 1]);

    // --- Verificacao de pos-condicao: atingibilidade preservada ---
    if (!verificaAtingibilidade(V, adj, resultado)) {
        cerr << "[Redei] AVISO: Atingibilidade nao totalmente preservada." << endl;
    } else {
        cout << "[Redei] OK: Atingibilidade preservada." << endl;
    }

    cout << "[Redei] Caminho Hamiltoniano encontrado: ";
    for (int i = 0; i < (int)ordem.size(); i++) {
        cout << ordem[i];
        if (i + 1 < (int)ordem.size()) cout << " -> ";
    }
    cout << endl;

    return resultado;
}