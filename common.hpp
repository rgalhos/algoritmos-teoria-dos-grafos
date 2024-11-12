#ifndef COMMON_HPP
#define COMMON_HPP

#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

#define INFINITY_DOUBLE std::numeric_limits<double>::infinity()
#define INFINITY_INT std::numeric_limits<int>::infinity()

template <typename T = double> using matrix = std::vector<std::vector<T>>;

struct program_params {
  const char *input;
  const char *output;
  int initial;
  bool solution;
};

class Tee {
private:
  std::ofstream &of;

public:
  Tee(std::ofstream &);

  Tee &operator<<(std::ostream &(*)(std::ostream &));

  template <typename T> Tee &operator<<(const T &val) {
    std::cout << val;
    if (of.is_open())
      of << val;

    return *this;
  }

  void close();
};

std::tuple<int, int, matrix<>> read_file(std::ifstream &, bool, bool);

#endif