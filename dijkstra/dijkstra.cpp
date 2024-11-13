#include "../common.hpp"
#include <cstdlib>
#include <vector>

const char *__ALGNAME = "DIJKSTRA";

struct node_t {
  int id;
  float weight;
};

// Queue implementada com heap (common.hpp)
PriorityQueue<node_t> pqueue([](const node_t &a, const node_t &b) {
  return a.weight > b.weight;
});

bool operator<(const node_t &a, const node_t &b) { return a.weight > b.weight; }

std::vector<int> get_neighbors(const matrix<double> adj_matrix, int vertex) {
  std::vector<int> adj;

  for (int i = 1; i < adj_matrix.size() - 1; i++) {
    if (adj_matrix[vertex][i] > 0) {
      adj.push_back(i);
    }
  }

  return adj;
}

auto dijkstra(const int n_vertex, const matrix<> &adj_matrix,
              const int initial_node) {
  std::vector<bool> visited(n_vertex + 1, false);
  // Matriz de custo setada com infinito
  std::vector<double> total_cost(n_vertex + 1, INFINITY_DOUBLE);

  // Coloca o vértice inicial na fila com peso 0
  pqueue.push((node_t){.id = initial_node, .weight = 0});
  total_cost[initial_node] = 0;

  while (!pqueue.empty()) {
    node_t curr_vertex = pqueue.pop();

    visited[curr_vertex.id] = true;
    auto neighbors = get_neighbors(adj_matrix, curr_vertex.id);

    for (const auto &neighbor : neighbors) {
      if (!visited[neighbor]) {
        float new_weight =
            curr_vertex.weight + adj_matrix[curr_vertex.id][neighbor];

        if (new_weight < total_cost[neighbor]) {
          total_cost[neighbor] = new_weight;

          pqueue.push((node_t){.id = neighbor, .weight = new_weight});
        }
      }
    }
  }

  return total_cost;
}

int __main(struct program_params params, std::ifstream &fin, Tee &fout) {
  auto [n_vertex, n_edges, adj_matrix] = read_file(fin, true, false);
  int initial_node = params.initial;

  if (initial_node == -1) {
    std::cerr << "Nenhum vértice inicial fornecido" << std::endl;
    std::cout << "Nenhum vértice inicial fornecido" << std::endl;

    return EXIT_FAILURE;
  }

  auto total_cost = dijkstra(n_vertex, adj_matrix, initial_node);

  // Printa
  for (int i = 1; i < n_vertex; i++) {
    if (i != initial_node) {
      if (total_cost[i] != INFINITY_DOUBLE) {
        fout << i << ":" << total_cost[i] << " ";
      } else {
        fout << i << ":-1 ";
      }
    } else {
      fout << i << ":0 ";
    }
  }

  fout << std::endl;

  return 0;
}