#include "common.hpp"
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <ostream>

// Métodos que serão fornecidos pelo algoritmo:
extern const char *__ALGNAME;
extern int __main(struct program_params, std::ifstream &, Tee &);

namespace fs = std::filesystem;

// Parâmetros passados pelo usuário
struct program_params params {
  .input = NULL, .output = NULL, .initial = -1, .solution = false,
};

static const struct option options[] = {
    {"help", no_argument, NULL, 'h'},
    {"output", required_argument, NULL, 'o'},
    {"file", required_argument, NULL, 'f'},
    {"solution", no_argument, NULL, 's'},
    {"initial", required_argument, NULL, 'i'},
    {NULL, 0, NULL, 0},
};

void print_usage(char **argv) {
  std::cerr << argv[0]
            << " [-h] [-s] [-i <vértice>] [-o <arquivo de saída>] -f <arquivo "
               "de entrada>"
            << std::endl;

  std::cerr << R"(
  -h           : mostra o help
  -o <arquivo> : redireciona a saida para o arquivo
  -f <arquivo> : indica o arquivo que contém o grafo de entrada
  -s           : mostra a solução (se aplicável)
  -i <vértice> : vértice inicial (para o algoritmo de Prim))"
            << std::endl;

  exit(EXIT_FAILURE);
}

void check_file(const char *f) {
  fs::path fin(f);
  std::error_code ec;

  if (fs::exists(fin, ec) || !ec) {
    auto perms = fs::status(fin, ec).permissions();

    if ((perms & fs::perms::owner_read) != fs::perms::none &&
        (perms & fs::perms::group_read) != fs::perms::none &&
        (perms & fs::perms::others_read) != fs::perms::none) {
      return;
    }
  }

  std::cerr << "Não foi possível ler ou abrir o arquivo de entrada"
            << std::endl;

  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  int opt;
  while ((opt = getopt_long(argc, argv, "hf:o:i:s", options, NULL)) != -1) {
    switch (opt) {
    case 'h':
      print_usage(argv);
      break;
    case 'f':
      params.input = optarg;
      break;
    case 'o':
      params.output = optarg;
      break;
    case 'i':
      params.initial = atoi(optarg);
      break;
    case 's':
      params.solution = true;
      break;
    case '?':
      std::cerr << "Parâmetro inválido: " << optopt << std::endl;
      print_usage(argv);
      break;
    }
  }

  if (NULL == params.input) {
    std::cerr << "Erro: Sem arquivo de entrada" << std::endl;
    print_usage(argv);
  }

  check_file(params.input);

  std::ifstream fin(params.input);

  std::ofstream of;
  if (NULL != params.output) {
    of.open(params.output);
  }

  Tee fout(of);

  int ret = __main(params, fin, fout);

  fin.close();
  fout.close();

  return ret;
}
