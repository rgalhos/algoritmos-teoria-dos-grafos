#include "common.hpp"

Tee::Tee(std::ofstream &of) : of(of) {}

Tee &Tee::operator<<(std::ostream &(*manip)(std::ostream &)) {
  std::cout << manip;
  if (of.is_open())
    of << manip;

  return *this;
}

void Tee::close() {
  if (this->of.is_open())
    this->of.close();
}

std::tuple<int, int, matrix<>> read_file(std::ifstream &fin, bool has_weight,
                                         bool is_directed) {
  int n_vertex, n_edges, v1, v2;
  double weight = 1;

  fin >> n_vertex >> n_edges;
  n_vertex++;

  matrix<> adj_matrix =
      std::vector(n_vertex + 1, std::vector<double>(n_vertex + 1, 0));

  for (int i = 0; i < n_edges; i++) {
    if (has_weight)
      fin >> v1 >> v2 >> weight;
    else
      fin >> v1 >> v2;

    adj_matrix[v1][v2] = weight;
    if (!is_directed)
      adj_matrix[v2][v1] = weight;
  }

  return {n_vertex, n_edges, adj_matrix};
}
