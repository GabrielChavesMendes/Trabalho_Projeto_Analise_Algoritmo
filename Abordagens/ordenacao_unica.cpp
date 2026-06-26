#include "../algoritmos.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// DFS para verificar atingibilidade (usada na pos-condicao)
static void dfsAtingibilidadeOrd(int u, const vector<vector<int>>& adj,
                                  vector<bool>& visitado) {
    visitado[u] = true;
    for (int v : adj[u])
        if (!visitado[v])
            dfsAtingibilidadeOrd(v, adj, visitado);
}

static bool verificaAtingibilidadeOrd(int V,
                                       const vector<vector<int>>& original,
                                       const vector<vector<int>>& resultado) {
    for (int src = 0; src < V; src++) {
        vector<bool> alcOrig(V, false), alcRes(V, false);
        dfsAtingibilidadeOrd(src, original, alcOrig);
        dfsAtingibilidadeOrd(src, resultado, alcRes);

        for (int dst = 0; dst < V; dst++) {
            if (dst == src) continue;
            if (alcOrig[dst] != alcRes[dst]) {
                cerr << "[Ordenacao] AVISO: Atingibilidade perdida: "
                     << src << " -> " << dst << endl;
                return false;
            }
        }
    }
    return true;
}

/*
 * Reducao Hamiltoniana por Ordenacao Topologica Unica.
 *
 * Se um DAG possui exatamente uma ordenacao topologica, esse caminho e,
 * por definicao matematica, o Caminho Hamiltoniano e a Reducao Transitiva
 * absoluta do grafo.
 *
 * Detecta unicidade via Kahn: em cada passo, a fila de grau-zero deve
 * ter exatamente 1 vertice. Caso contrario, a ordenacao nao e unica e
 * o metodo nao e aplicavel diretamente.
 *
 * Pre-condicao: grafo deve ser DAG com ordenacao topologica unica.
 * Pos-condicao: preserva a mesma atingibilidade do grafo original.
 */
vector<vector<int>> reducaoHamiltonianaOrdenacao(int V, const vector<vector<int>>& adj) {
    // --- Calcula graus de entrada ---
    vector<int> grauEntrada(V, 0);
    for (int u = 0; u < V; u++)
        for (int v : adj[u])
            grauEntrada[v]++;

    // --- Kahn com verificacao de unicidade ---
    // Unicidade: em cada iteracao, a fila deve ter EXATAMENTE 1 elemento
    queue<int> fila;
    for (int u = 0; u < V; u++)
        if (grauEntrada[u] == 0)
            fila.push(u);

    vector<int> ordem;
    ordem.reserve(V);
    bool ordenacaoUnica = true;

    while (!fila.empty()) {
        // Mais de um vertice com grau zero → ordenacao ambigua
        if (fila.size() > 1) {
            cerr << "[Ordenacao] AVISO: Ordenacao topologica NAO e unica "
                 << "(multiplos vertices com grau de entrada 0 simultaneamente)." << endl;
            ordenacaoUnica = false;
        }

        int u = fila.front();
        fila.pop();
        ordem.push_back(u);

        for (int v : adj[u]) {
            grauEntrada[v]--;
            if (grauEntrada[v] == 0)
                fila.push(v);
        }
    }

    // --- Detecta ciclo (grafo nao e DAG) ---
    if ((int)ordem.size() != V) {
        cerr << "[Ordenacao] ERRO: Grafo contem ciclo. "
             << "Reducao transitiva por ordenacao unica nao se aplica. "
             << "Retornando grafo vazio." << endl;
        return vector<vector<int>>(V);
    }

    if (!ordenacaoUnica) {
        cerr << "[Ordenacao] AVISO: Resultado pode nao ser a reducao transitiva "
             << "real pois a ordenacao nao e unica. "
             << "Considere usar outro metodo para este grafo." << endl;
    } else {
        cout << "[Ordenacao] OK: Ordenacao topologica e unica." << endl;
    }

    // --- Monta sub-grafo ligando ordem[i] -> ordem[i+1] ---
    vector<vector<int>> resultado(V);
    for (int i = 0; i + 1 < V; i++)
        resultado[ordem[i]].push_back(ordem[i + 1]);

    // --- Verificacao de pos-condicao: atingibilidade preservada ---
    if (!verificaAtingibilidadeOrd(V, adj, resultado)) {
        cerr << "[Ordenacao] AVISO: Atingibilidade nao totalmente preservada." << endl;
    } else {
        cout << "[Ordenacao] OK: Atingibilidade preservada." << endl;
    }

    cout << "[Ordenacao] Caminho Hamiltoniano encontrado: ";
    for (int i = 0; i < (int)ordem.size(); i++) {
        cout << ordem[i];
        if (i + 1 < (int)ordem.size()) cout << " -> ";
    }
    cout << endl;

    return resultado;
}