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

void dfs_transposed(const matrix<> &transposed_graph,
                    std::vector<bool> &visited, matrix<int> &components,
                    int curr_vertex) {
  int n_vertex = transposed_graph.size() - 1;

  components[components.size() - 1].push_back(curr_vertex);
  visited[curr_vertex] = true;

  for (int i = 1; i < n_vertex; i++) {
    if (!visited[i] && transposed_graph[curr_vertex][i]) {
      dfs_transposed(transposed_graph, visited, components, i);
    }
  }
}

matrix<int> kosaraju(const matrix<> &adj_matrix, Tee &fout) {
  int n_vertex = adj_matrix.size() - 1;

  std::stack<int> stack;
  std::vector<bool> visited(n_vertex, false);
  matrix<int> components;
  int num_components = 0;

  // Grafo transposto
  matrix<> transposed_graph =
      std::vector(n_vertex + 1, std::vector<double>(n_vertex, 0));

  for (int i = 0; i < n_vertex; i++) {
    for (int j = 0; j < n_vertex; j++) {
      transposed_graph[i][j] = adj_matrix[j][i];
    }
  }

  for (int i = 1; i < n_vertex; i++) {
    if (!visited[i]) {
      dfs(adj_matrix, visited, stack, i);
    }
  }

  // Reseta array de visitados
  std::fill(visited.begin(), visited.end(), false);

  while (!stack.empty()) {
    int vertex = stack.top();
    stack.pop();

    if (!visited[vertex]) {
      ++num_components;
      components.push_back(std::vector<int>());

      dfs_transposed(transposed_graph, visited, components, vertex);
    }
  }

  return components;
}

int __main(struct program_params params, std::ifstream &fin, Tee &fout) {
  auto [n_vertex, n_edges, adj_matrix] = read_file(fin, false, true);

  auto components = kosaraju(adj_matrix, fout);

  for (const auto &component : components) {
    for (const auto &vertex : component) {
      fout << vertex << " ";
    }

    fout << std::endl;
  }

  return 0;
}