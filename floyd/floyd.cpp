#include "../common.hpp"
#include <cstdio>
#include <ostream>

const char *__ALGNAME = "FLOYD";

void floyd(matrix<double> &adj_matrix, matrix<double> &dist_matrix) {
  int n_vertex = adj_matrix.size() - 1;

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
}

int __main(struct program_params params, std::ifstream &fin, Tee &fout) {
  auto [n_vertex, n_edges, adj_matrix] = read_file(fin, true);
  matrix<double> dist_matrix(adj_matrix);

  floyd(adj_matrix, dist_matrix);

  // Print
  for (int i = 1; i < n_vertex; i++) {
    for (int j = 1; j < n_vertex; j++) {
      char str[8];
      snprintf(str, 8, "%5.1lf ", dist_matrix[i][j]);
      fout << str;
    }

    fout << std::endl;
  }

  return 0;
}