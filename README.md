# Trabalho PAA - Redução Transitiva de Grafos

Este repositório contém a implementação do trabalho da disciplina **Projeto e Análise de Algoritmos**, desenvolvido em C++, com foco no estudo de algoritmos para **redução transitiva de grafos**.

A redução transitiva busca remover arestas redundantes de um grafo preservando as relações de atingibilidade entre os vértices. Em outras palavras, se um vértice `v` continua sendo alcançável a partir de `u` por outro caminho, uma aresta direta entre eles pode ser considerada redundante.

## Objetivo

Implementar e comparar diferentes abordagens baseadas em caminhamento em grafos para realizar a redução transitiva, analisando desempenho, complexidade e comportamento em diferentes topologias.

## Algoritmos implementados

As implementações estão organizadas na pasta `Abordagens/`:

* `dfs.cpp` - redução por busca em profundidade.
* `bfs.cpp` - redução por busca em largura.
* `dfsMemoizationDP.cpp` - abordagem com reaproveitamento de resultados.
* `dfsTopologia.cpp` - abordagem baseada em DFS e ordenação topológica.
* `otimizacaoBitset.cpp` - otimização com `bitset` para representação de atingibilidade.
* `warshall.cpp` - abordagem matricial baseada no fecho transitivo.
* `tarjanSCC.cpp` - tratamento de componentes fortemente conexas.
* `kahn.cpp` - ordenação topológica pelo algoritmo de Kahn.
* `ordenacao_unica.cpp` - verificação de ordenação topológica única.
* `redei.cpp` - abordagem para grafos de torneio baseada no Teorema de Rédei.
* `guloso.cpp` - heurística gulosa para busca de caminho Hamiltoniano.

## Estrutura do projeto

```text
.
├── Abordagens/
│   ├── bfs.cpp
│   ├── dfs.cpp
│   ├── dfsMemoizationDP.cpp
│   ├── dfsTopologia.cpp
│   ├── guloso.cpp
│   ├── kahn.cpp
│   ├── ordenacao_unica.cpp
│   ├── otimizacaoBitset.cpp
│   ├── redei.cpp
│   ├── tarjanSCC.cpp
│   └── warshall.cpp
├── algoritmos.h
├── main.cpp
├── Trabalho_PAA.cbp
├── .gitignore
└── README.md
```

## Compilação

Para compilar pelo terminal com `g++`, utilize:

```bash
g++ -std=c++17 main.cpp Abordagens/*.cpp -o trabalho_paa
```

## Execução

Após compilar, execute:

```bash
./trabalho_paa
```

No Windows, caso o executável seja gerado como `.exe`:

```bash
trabalho_paa.exe
```

## Representação dos grafos

A representação principal utilizada foi por **listas de adjacência**, adequada para grafos esparsos e para algoritmos baseados em caminhamento, pois permite percorrer diretamente os vizinhos de cada vértice.

Também foram utilizadas abordagens com **matriz de adjacência**, especialmente no algoritmo de Warshall, pois sua formulação depende da verificação direta de conexões entre pares de vértices.

## Grafos não direcionados

As implementações foram pensadas principalmente para grafos direcionados, pois a definição de redução transitiva está diretamente associada à preservação da atingibilidade direcionada.

Em grafos não direcionados, o comportamento muda, já que as arestas representam conexões bidirecionais. Nesse caso, preservar atingibilidade se aproxima mais da preservação de conectividade, podendo gerar estruturas semelhantes a árvores geradoras em algumas abordagens. Por isso, nem todas as técnicas aplicadas a grafos direcionados se comportam da mesma forma em grafos não direcionados.

## Relatório

O relatório do projeto apresenta:

* justificativa da representação dos grafos;
* descrição das implementações;
* análise de complexidade;
* testes realizados;
* comparação entre abordagens;
* discussão sobre grafos não direcionados;
* responsabilidades dos membros do grupo.

## Autores

* Alessandra Faria Rodrigues
* Daniel Victor Rocha Costa
* Felipe Barros Ratton de Almeida
* Gabriel Chaves Mendes
* Gabriela de Assis dos Reis
* Guilherme Henrique da Silva Teodoro
* Gustavo Henrique R. de Castro
