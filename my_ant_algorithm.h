#ifndef A2_SimpleNavigator_v1_0_CPP_1_ANT_ALGORITHM_H
#define A2_SimpleNavigator_v1_0_CPP_1_ANT_ALGORITHM_H

#include <cmath>
#include <experimental/random>

#include "my_graph.h"
#include "my_matrix_oop.h"

namespace my {

struct Ant {
  int start_point;
  std::vector<int> route;
  int route_length;
};

class AntAlgorithm {
 public:
  AntAlgorithm(Graph &graph);

  Ant Solution();
  std::vector<int> GetRoute();
  int GetRouteLenght();

 private:
  void AntsRoutePlanning();
  void RoutePlanning(Ant &ant);
  void PheromoneSupplement();
  void FormulaPheromoneSupplement(int i, int j);
  bool AntPheromoneAdd(int i, int j, const std::vector<int> &route);
  void ChoiceDirection(Ant &ant, int k);
  void PheromoneMatrixInit();
  void ProximityTableCompletion(Graph graph);
  void AntsStartPointInit();
  bool CheckVertexIsNotPassed(const std::vector<int> &route, int vertex);

  int size_;
  std::vector<Ant> ants_;
  double start_pheromon_ = 0.5;
  double q_const_ = 1.0;
  double pheromone_vaporization_coefficient = 0.64;
  int coef_alpha_ = 1;
  int coef_beta_ = 1;
  S21Matrix pheromone_matrix_;
  S21Matrix proximity_table_;
  S21Matrix adjacent_matrix_;

  Ant min_path_;
};

}  // namespace my

#endif  // A2_SimpleNavigator_v1_0_CPP_1_ANT_ALGORITHMS_H