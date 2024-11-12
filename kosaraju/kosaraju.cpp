#include "../common.hpp"
#include <stack>
#include <vector>

const char *__ALGNAME = "KOSARAJU";

void dfs(const matrix<> &adj_matrix, std::vector<bool> &visited,
         std::stack<int> &stack, int curr_vertex) {
  int n_vertex = adj_matrix.size() - 1;

  visited[curr_vertex] = true;

  for (int i = 1; i < n_vertex; i++) {
    if (!visited[i] && adj_matrix[curr_vertex][i]) {
      dfs(adj_matrix, visited, stack, i);
    }
  }

  stack.push(curr_vertex);
}

void dfs_transposed(const matrix<> &adj_matrix, std::vector<bool> &visited,
                    int curr_vertex, Tee &fout) {
  int n_vertex = adj_matrix.size() - 1;

  visited[curr_vertex] = true;

  fout << curr_vertex << " ";

  for (int i = 1; i < n_vertex; i++) {
    if (!visited[i] && adj_matrix[curr_vertex][i]) {
      dfs_transposed(adj_matrix, visited, i, fout);
    }
  }
}

void kosaraju(const matrix<> &adj_matrix, Tee &fout) {
  int n_vertex = adj_matrix.size() - 1;

  std::stack<int> stack;
  std::vector<bool> visited(n_vertex + 1, false);

  // Grafo transposto
  matrix<> transposed_graph =
      std::vector(n_vertex + 1, std::vector<double>(n_vertex, 0));

  for (int i = 1; i < n_vertex; i++) {
    for (int j = 1; j < n_vertex; j++) {
      transposed_graph[i][j] = adj_matrix[j][i];
    }
  }

  // DFS
  for (int i = 1; i < n_vertex; i++) {
    if (!visited[i]) {
      dfs(adj_matrix, visited, stack, i);
    }
  }

  // Reseta array de visitados
  std::fill(visited.begin(), visited.end(), false);

  // DFS no grafo transposto usando os vértices na pilha
  while (!stack.empty()) {
    int vertex = stack.top();
    stack.pop();

    if (!visited[vertex]) {
      dfs_transposed(transposed_graph, visited, vertex, fout);

      fout << std::endl;
    }
  }
}

int __main(struct program_params params, std::ifstream &fin, Tee &fout) {
  auto [n_vertex, n_edges, adj_matrix] = read_file(fin, false, true);

  kosaraju(adj_matrix, fout);

  return 0;
}