#include "my_ant_algorithm.h"

namespace my {

std::vector<int> AntAlgorithm::GetRoute() { return min_path_.route; }
int AntAlgorithm::GetRouteLenght() { return min_path_.route_length; }

Ant AntAlgorithm::Solution() {
  AntsStartPointInit();
  for (int i = 0; i < 500; i++) {
    AntsRoutePlanning();
    PheromoneSupplement();
  }
  return min_path_;
}

void AntAlgorithm::AntsRoutePlanning() {
  for (size_t i = 0; i < ants_.size(); i++) {
    RoutePlanning(ants_[i]);
  }
}

void AntAlgorithm::RoutePlanning(Ant &ant) {
  ant.route.clear();
  ant.route_length = 0;
  ant.route.push_back(ant.start_point - 1);
  for (int i = 0; i < size_; i++) {
    ChoiceDirection(ant, ant.route[i]);
  }
  ant.route_length +=
      adjacent_matrix_(ant.route[ant.route.size() - 1], ant.route[0]);
  if (ant.route_length < min_path_.route_length &&
      (int)ant.route.size() == size_) {
    min_path_.route = ant.route;
    min_path_.route_length = ant.route_length;
  }
}

void AntAlgorithm::ChoiceDirection(Ant &ant, int k) {
  double sd = 0;
  std::vector<int> adjacent_vertices;
  for (int i = 0; i < size_; i++) {
    if (adjacent_matrix_(k, i) != 0) {
      if (CheckVertexIsNotPassed(ant.route, i)) {
        adjacent_vertices.push_back(i);
      }
    }
  }
  std::vector<double> desire_to_pass;
  double sum_desire = 0;
  for (int i = 0; i < (int)adjacent_vertices.size(); i++) {
    sd = pow(pheromone_matrix_(k, adjacent_vertices[i]), coef_alpha_) *
         pow(proximity_table_(k, adjacent_vertices[i]), coef_beta_);
    desire_to_pass.push_back(sd);
    sum_desire += sd;
  }
  if (sum_desire != 0) {
    for (int i = 0; i < (int)desire_to_pass.size(); i++) {
      desire_to_pass[i] = desire_to_pass[i] / sum_desire;
    }
  }
  double random = std::experimental::randint(1, 999) / 1000.0;
  for (int i = 0; i < (int)adjacent_vertices.size(); i++) {
    if (random > 0 && random < desire_to_pass[i]) {
      ant.route.push_back(adjacent_vertices[i]);
      ant.route_length += adjacent_matrix_(k, adjacent_vertices[i]);
    }
    random -= desire_to_pass[i];
  }
}

bool AntAlgorithm::CheckVertexIsNotPassed(const std::vector<int> &route,
                                          int vertex) {
  for (int i = 0; i < (int)route.size(); i++) {
    if (route[i] == vertex) return false;
  }
  return true;
}

void AntAlgorithm::AntsStartPointInit() {
  for (size_t i = 0; i < ants_.size(); i++) {
    ants_[i].start_point = i + 1;
    ants_[i].route.reserve(size_);
  }
}

// Pheromone Supplement begin

void AntAlgorithm::PheromoneSupplement() {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      FormulaPheromoneSupplement(i, j);
    }
  }
}

void AntAlgorithm::FormulaPheromoneSupplement(int i, int j) {
  double pheromone_summ = 0;
  for (int k = 0; k < size_; k++) {
    if (ants_[k].route_length && AntPheromoneAdd(i, j, ants_[k].route)) {
      pheromone_summ += q_const_ / ants_[k].route_length;
    }
  }
  pheromone_matrix_(i, j) =
      pheromone_vaporization_coefficient * pheromone_matrix_(i, j) +
      pheromone_summ;
}

bool AntAlgorithm::AntPheromoneAdd(int i, int j,
                                   const std::vector<int> &route) {
  for (size_t k = 0; k < route.size() - 1; k++) {
    if ((route[k] == i && route[k + 1] == j) ||
        (route[k] == j && route[k + 1] == i)) {
      return true;
    }
  }
  return false;
}

// Pheromone Supplement end

AntAlgorithm::AntAlgorithm(Graph &graph)
    : size_(graph.Size()),
      ants_(size_),
      pheromone_matrix_(size_, size_),
      proximity_table_(size_, size_),
      adjacent_matrix_(size_, size_) {
  ProximityTableCompletion(graph);
  PheromoneMatrixInit();
  // ants_.reserve(size_);
  min_path_.route_length = 2147483647;
}

void AntAlgorithm::PheromoneMatrixInit() {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      pheromone_matrix_(i, j) = start_pheromon_;
    }
  }
}

void AntAlgorithm::ProximityTableCompletion(Graph graph) {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      if (graph(i + 1, j + 1) != 0) {
        proximity_table_(i, j) = q_const_ / graph(i + 1, j + 1);
      }
    }
  }
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      adjacent_matrix_(i, j) = graph(i + 1, j + 1);
    }
  }
}
}  // namespace my