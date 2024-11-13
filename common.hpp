#ifndef COMMON_HPP
#define COMMON_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

#define INFINITY_DOUBLE std::numeric_limits<double>::infinity()
#define INFINITY_INT std::numeric_limits<int>::infinity()

template <typename T = double> using matrix = std::vector<std::vector<T>>;

std::tuple<int, int, matrix<>> read_file(std::ifstream &, bool, bool);

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

template <typename T> class PriorityQueue {
private:
  std::vector<T> heap;
  int n_elements = 0;
  bool (*compare)(const T &, const T &);

public:
  PriorityQueue(bool (*compare)(const T &, const T &)) : compare(compare) {
    std::make_heap(heap.begin(), heap.end(), compare);
  }

  void push(T el) {
    heap.push_back(el);
    std::push_heap(heap.begin(), heap.end(), compare);
    ++n_elements;
  }

  T pop() {
    T el = heap.front();
    std::pop_heap(heap.begin(), heap.end(), compare);
    heap.pop_back();
    --n_elements;

    return el;
  }

  bool empty() { return this->n_elements <= 0; }
};

#endif