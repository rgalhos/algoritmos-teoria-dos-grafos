#include "../common.hpp"
#include <csignal>
#include <ostream>

const char *__ALGNAME = "PRIM";

typedef struct {
  int id;
  float weight;
} node_t;

std::vector<int> get_neighbors(const matrix<> adj_matrix, int vertex) {
  std::vector<int> adj;

  for (int i = 1; i < adj_matrix.size() - 1; i++) {
    if (adj_matrix[vertex][i] > 0) {
      adj.push_back(i);
    }
  }

  return adj;
}

std::pair<int, std::vector<std::pair<int, int>>>
prim(const matrix<> &adj_matrix, const int initial) {
  int n_vertex = adj_matrix.size() - 1;

  std::vector<double> min_weight(n_vertex + 1, INFINITY_DOUBLE);
  std::vector<bool> visited(n_vertex + 1, false);
  std::vector<int> parent(n_vertex + 1, 0);
  // Fila de prioridade com heap (common.hpp)
  PriorityQueue<node_t> pqueue(
      [](const node_t &a, const node_t &b) { return a.weight > b.weight; });

  std::vector<std::pair<int, int>> mst_edges;
  int total_cost = 0;

  min_weight[initial] = 0;
  parent[initial] = 0;
  pqueue.push((node_t){.id = initial, .weight = 0});

  while (!pqueue.empty()) {
    node_t node = pqueue.pop();
    int vertex = node.id;
    float weight = node.weight;

    if (visited[vertex])
      continue;

    visited[vertex] = true;
    total_cost += weight;

    if (parent[vertex]) {
      mst_edges.push_back({parent[vertex], vertex});
    }

    auto neighbors = get_neighbors(adj_matrix, vertex);

    for (const auto &neighbor : neighbors) {
      float edge_weight = adj_matrix[vertex][neighbor];

      if (!visited[neighbor] && min_weight[neighbor] > edge_weight) {
        min_weight[neighbor] = edge_weight;
        parent[neighbor] = vertex;

        pqueue.push((node_t){.id = neighbor, .weight = edge_weight});
      }
    }
  }

  return {total_cost, mst_edges};
}

int __main(struct program_params params, std::ifstream &fin, Tee &fout) {
  auto [n_vertex, n_edges, adj_matrix] = read_file(fin, true, false);
  int initial_node = params.initial;

  if (initial_node == -1) {
    std::cerr << "Nenhum vértice inicial fornecido" << std::endl;

    return EXIT_FAILURE;
  }

  auto [total_cost, mst_edges] = prim(adj_matrix, initial_node);

  // Print
  if (params.solution) {
    for (int i = 1; i < mst_edges.size(); i++) {
      auto [first, second] = mst_edges[i];

      fout << "(" << first << "," << second << ") ";
    }

    fout << std::endl;
  } else {
    fout << total_cost << std::endl;
  }

  return 0;
}