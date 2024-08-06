#ifndef A2_SimpleNavigator_v1_0_CPP_1_GRAPH_ALGORITMS_H
#define A2_SimpleNavigator_v1_0_CPP_1_GRAPH_ALGORITMS_H

#include "my_ant_algorithm.h"
#include "my_graph.h"
#include "my_queue.h"
#include "my_stack.h"

namespace my {

struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

class GraphAlgorithms {
 public:
  GraphAlgorithms() {}

  static std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  static std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  static std::vector<std::vector<int>> GetLeastSpanningTree(Graph &graph);
  static TsmResult SolveTravelingSalesmanProblem(Graph &graph);
  static int GetShortestPathBetweenVertices(my::Graph &graph, int vertex1,
                                            int vertex2);
  static std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      my::Graph &graph);

 private:
  static void AddEdges(std::vector<int> &visited, Graph &ostov, Graph &graph);
  static void AdjacentVerticesSearch(Stack &stack, int vertex, Graph &graph,
                                     std::vector<int> &push_in_stack_control);
  static bool CheckVertexIsNotPassed(std::vector<int> push_in_stack_control,
                                     int vertex);
  static void BFSAdjacentVerticesSearch(
      Queue &queue, int vertex, Graph &graph,
      std::vector<int> &push_in_queue_control);
};

}  // namespace my

#endif  // A2_SimpleNavigator_v1_0_CPP_1_GRAPH_ALGORITMS_H
