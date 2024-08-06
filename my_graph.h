#ifndef A2_SimpleNavigator_v1_0_CPP_1_S21_GRAPH_H
#define A2_SimpleNavigator_v1_0_CPP_1_S21_GRAPH_H

#include <fstream>
#include <iostream>
#include <vector>

namespace my {

class Graph {
 public:
  Graph();
  Graph(std::string filename);

  int& operator()(int i, int j);

  int Size();
  void SetSize(int size);

  void LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);

  void DeleteNode(int column);
  void AppendNode();
  void Print();
  std::vector<int> AdjacentVertices(int vertex);
  std::vector<int> AdjacentMatrix();
  std::vector<std::vector<int> > AdjacencyMatrix();
  static void PrintAdjacencyMatrix(std::vector<std::vector<int> > matrix);

 private:
  int size_;
  std::vector<int> matrix_;
};

}  // namespace my

#endif  // A2_SimpleNavigator_v1_0_CPP_1_S21_GRAPH_H