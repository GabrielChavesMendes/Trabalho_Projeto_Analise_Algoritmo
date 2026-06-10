#ifndef ALGORITMOS_H_INCLUDED
#define ALGORITMOS_H_INCLUDED

#include <vector>
#include <string>

// Função auxiliar compartilhada para imprimir os resultados
void printGrafo(const std::string& titulo, const std::vector<std::vector<int>>& adj);

// Declaração dos Métodos de Redução (Vocês vão adicionando as outras aqui)
std::vector<std::vector<int>> reducaoDFS(int V, const std::vector<std::vector<int>>& adj);
std::vector<std::vector<int>> reducaoBFS(int V, const std::vector<std::vector<int>>& adj);

#endif // ALGORITMOS_H_INCLUDED
