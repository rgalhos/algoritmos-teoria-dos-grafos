## Projeto da disciplina de Teoria dos Grafos 2024.1 - COMP369.

Implementação dos algoritmos Dijkstra, Kosaraju, Kruskal, Prim e Floyd-Warshall.

Os algoritmos estão separados em pastas. Cada pasta contém a implementação do algoritmo e um arquivo makefile.

### Compilação

Este projeto requer o GNU Make e GCC/G++ (com suporte ao C++20).

Há um makefile geral na raíz do projeto e um makefile na pasta de cada algoritmo (este apenas aponta para o makefile da raíz).

Após rodar o comando `make`, os binários poderão ser encontrados tanto na pasta `./build` quanto na pasta de cada algoritmo.

```shell
# Compilando um algoritmo específico (dentro de sua pasta)
cd ./nome_algoritmo
make
./nome_algoritmo


# Compilando um algorítmo específico (a partir da raíz do projeto)
make nome_algoritmo
./build/nome_algoritmo
# OU
./nome_algoritmo/nome_algoritmo


# Compilando todos os algorítmos
make all
# Os executáveis estarão tanto na pasta ./build quanto na pasta de cada algorítmo


# Apagando os binários
make clean
```

### Execução

```
./nome_algoritmo [-h] [-s] [-i <vértice>] [-o <arquivo de saída>] -f <arquivo de entrada>

  -h           : mostra o help
  -o <arquivo> : redireciona a saida para o arquivo
  -f <arquivo> : indica o arquivo que contém o grafo de entrada
  -s           : mostra a solução (se aplicável)
  -i <vértice> : vértice inicial (para o algoritmo de Prim)
```

#### Arquivo de entrada

O arquivo de entrada deve estar no seguinte formato:

```
|V| |E|
```

Seguido de |E| linhas dessa forma:

```
Vn Vm W(VnVm)
```

Sendo:

- `|V|` o número de vértices
- `|E|` o número de arestas
- `Vn` e `Vm` vértices de V
- `W(VnVm)` o peso da aresta VnVm (deve ser omitido em grafos sem peso)
