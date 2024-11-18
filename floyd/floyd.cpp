#include "../common.hpp"
#include <cstdio>
#include <ostream>

const char *__ALGNAME = "FLOYD";

matrix<> floyd_warshall(const matrix<> &adj_matrix) {
  int n_vertex = adj_matrix.size() - 1;
  matrix<> dist_matrix(adj_matrix);

  // Corrige a entrada para deixar vértices inalcançáveis com peso
  // infinito, mas mantendo 0 para i=j
  for (int i = 1; i < n_vertex; i++) {
    for (int j = 1; j < n_vertex; j++) {
      if (dist_matrix[i][j] == 0 && i != j) {
        dist_matrix[i][j] = INFINITY_DOUBLE;
      }
    }
  }

  // Floyd-Warshall:
  for (int k = 1; k < n_vertex; k++) {
    for (int i = 1; i < n_vertex; i++) {
      for (int j = 1; j < n_vertex; j++) {
        if (dist_matrix[i][k] != INFINITY_DOUBLE &&
            dist_matrix[k][j] != INFINITY_DOUBLE &&
            dist_matrix[i][j] > dist_matrix[i][k] + dist_matrix[k][j]) {
          dist_matrix[i][j] = dist_matrix[i][k] + dist_matrix[k][j];
        }
      }
    }
  }

  return dist_matrix;
}

int __main(struct program_params params, std::ifstream &fin, Tee &fout) {
  auto [n_vertex, n_edges, adj_matrix] = read_file(fin, true, true);

  auto dist_matrix = floyd_warshall(adj_matrix);

  for (int i = 1; i < n_vertex; i++) {
    for (int j = 1; j < n_vertex; j++) {
      fout << dist_matrix[i][j] << " ";
    }

    fout << std::endl;
  }

  return 0;
}