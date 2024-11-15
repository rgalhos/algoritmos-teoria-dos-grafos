#include "../common.hpp"
#include <algorithm>
#include <tuple>
#include <vector>

const char *__ALGNAME = "KRUSKAL";

typedef struct {
  double weight;
  int u;
  int v;
} edge_t;

int find(const int *parents, int vertex) {
  if (parents[vertex] != vertex) {
    return find(parents, parents[vertex]);
  }

  return vertex;
}

void unite(int *parents, int u, int v) {
  int x_root = find(parents, u);
  int y_root = find(parents, v);

  if (x_root != y_root) {
    parents[x_root] = y_root;
  }
}

std::tuple<int, std::vector<edge_t>> kruskal(const matrix<> adj_matrix) {
  int n_vertex = adj_matrix.size() - 1;

  int total_cost = 0;
  int parents[adj_matrix.size()];
  std::vector<edge_t> mst_edges;
  std::vector<edge_t> sorted_adj_matrix;

  for (int i = 1; i < n_vertex; i++) {
    parents[i] = i;

    for (int j = 1; j < n_vertex; j++) {
      if (adj_matrix[i][j]) {
        sorted_adj_matrix.push_back(
            (edge_t){.weight = adj_matrix[i][j], .u = i, .v = j});
      }
    }
  }

  // Ordena as arestas por peso em ordem crescente
  std::sort(
      sorted_adj_matrix.begin(), sorted_adj_matrix.end(),
      [](const edge_t &a, const edge_t &b) { return a.weight < b.weight; });

  for (const auto &edge : sorted_adj_matrix) {
    if (find(parents, edge.u) != find(parents, edge.v)) {
      unite(parents, edge.u, edge.v);

      total_cost += edge.weight;
      mst_edges.push_back(edge);
    }
  }

  return {total_cost, mst_edges};
}

int __main(struct program_params params, std::ifstream &fin, Tee &fout) {
  auto [n_vertex, n_edges, adj_matrix] = read_file(fin, true, false);

  auto [total_cost, mst_edges] = kruskal(adj_matrix);

  // Print
  if (params.solution) {
    for (const auto &edge : mst_edges) {
      fout << "(" << edge.u << "," << edge.v << ") ";
    }

    fout << std::endl;
  } else {
    fout << total_cost << std::endl;
  }

  return 0;
}