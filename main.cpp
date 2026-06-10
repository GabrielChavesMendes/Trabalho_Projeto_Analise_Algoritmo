#include <iostream>
#include "algoritmos.h"

using namespace std;

// Implementação da função de exibição compartilhada
void printGrafo(const string& titulo, const vector<vector<int>>& adj) {
    cout << "\n=== " << titulo << " ===" << endl;
    for (size_t i = 0; i < adj.size(); ++i) {
        cout << "Vertice " << i << " aponta para: ";
        for (int vizinho : adj[i]) cout << vizinho << " ";
        cout << endl;
    }
    cout << "=========================\n" << endl;
}

int main() {
    int V = 4;
    vector<vector<int>> listaAdj(V);
    listaAdj[0] = {1, 2, 3};
    listaAdj[1] = {2};
    listaAdj[2] = {3};
    listaAdj[3] = {};

    int opcao = -1;
    while (opcao != 0) {
        cout << "=== PAINEL DE METODOS MODULARES ===" << endl;
        cout << "1. Executar Modulo DFS" << endl;
        cout << "2. Executar Modulo BFS (Ainda nao implementado)" << endl;
        cout << "8. Exibir Grafo Original" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        vector<vector<int>> resultado;

        switch (opcao) {
            case 1:
                resultado = reducaoDFS(V, listaAdj);
                printGrafo("Resultado: Modulo DFS", resultado);
                break;
            case 2:
                cout << "\n[Aviso] O arquivo correspondente ao BFS precisa ser criado e implementado!\n" << endl;
                break;
            case 8:
                printGrafo("Grafo Original", listaAdj);
                break;
            case 0:
                cout << "Saindo do programa..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    }
    return 0;
}
