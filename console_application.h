#include "my_graph_algorithms.h"

namespace my {

class ConsoleApplication {
 public:
  int GraphSize();
  void LoadGraphFromFile();
  void ExportGraphToDot();
  void DepthFirstSearch();
  void BreadthFirstSearch();
  void GetShortestPathBetweenVertices();
  void GetShortestPathsBetweenAllVertices();
  void GetLeastSpanningTree();
  void SolveTravelingSalesmanProblem();

 private:
  int GetNumber();
  Graph graph_;
};

}  // namespace my