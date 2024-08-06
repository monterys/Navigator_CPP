#include "my_graph_algorithms.h"

namespace my {

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  AntAlgorithm ants(graph);
  ants.Solution();
  TsmResult result;
  for (auto value : ants.GetRoute()) {
    result.vertices.push_back(value + 1);
  }
  result.distance = ants.GetRouteLenght();
  return result;
}

std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  int size = graph.Size();
  std::vector<int> visited;
  Graph ostov;
  ostov.SetSize(size);
  visited.push_back(1);
  for (int i = 0; i < size - 1; i++) {
    AddEdges(visited, ostov, graph);
  }
  return ostov.AdjacencyMatrix();
}

void GraphAlgorithms::AddEdges(std::vector<int> &visited, Graph &ostov,
                               Graph &graph) {
  int min_edges = 2147483647;
  int add_vertex = 0;
  int current_vertex = 0;
  for (int i = 0; i < (int)visited.size(); i++) {
    for (int j = 1; j <= graph.Size(); j++) {
      if (graph(visited[i], j) < min_edges && graph(visited[i], j) != 0 &&
          CheckVertexIsNotPassed(visited, j)) {
        min_edges = graph(visited[i], j);
        add_vertex = j;
        current_vertex = visited[i];
      }
    }
  }
  visited.push_back(add_vertex);
  ostov(add_vertex, current_vertex) = min_edges;
  ostov(current_vertex, add_vertex) = min_edges;
}

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int start_vertex) {
  std::vector<int> visited;
  std::vector<int> push_in_stack_control;
  Stack stack;
  stack.push(start_vertex);
  push_in_stack_control.push_back(start_vertex);
  while (!stack.empty()) {
    int tmp = stack.pop();

    visited.push_back(tmp);
    AdjacentVerticesSearch(stack, tmp, graph, push_in_stack_control);
  }
  return visited;
}

void GraphAlgorithms::AdjacentVerticesSearch(
    Stack &stack, int vertex, Graph &graph,
    std::vector<int> &push_in_stack_control) {
  for (int i = graph.Size(); i > 0; i--) {
    if (graph(vertex, i) != 0 &&
        CheckVertexIsNotPassed(push_in_stack_control, i)) {
      stack.push(i);
      push_in_stack_control.push_back(i);
    }
  }
}

bool GraphAlgorithms::CheckVertexIsNotPassed(
    std::vector<int> push_in_stack_control, int vertex) {
  for (int i = 0; i < (int)push_in_stack_control.size(); i++) {
    if (push_in_stack_control[i] == vertex) return false;
  }
  return true;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  std::vector<int> visited;
  Queue queue;
  std::vector<int> push_in_queue_control;
  push_in_queue_control.push_back(start_vertex);
  queue.push(start_vertex);
  while (!queue.empty()) {
    int tmp = queue.pop();
    visited.push_back(tmp);
    BFSAdjacentVerticesSearch(queue, tmp, graph, push_in_queue_control);
  }
  return visited;
}

void GraphAlgorithms::BFSAdjacentVerticesSearch(
    Queue &queue, int vertex, Graph &graph,
    std::vector<int> &push_in_queue_control) {
  for (int i = 1; i <= graph.Size(); i++) {
    if (graph(vertex, i) != 0 &&
        CheckVertexIsNotPassed(push_in_queue_control, i)) {
      queue.push(i);
      push_in_queue_control.push_back(i);
    }
  }
}

int GraphAlgorithms::GetShortestPathBetweenVertices(my::Graph &graph,
                                                    int vertex1, int vertex2) {
  std::vector<bool> visited(graph.Size(), false);
  std::vector<int> path(graph.Size(), __INT32_MAX__);

  int current_vertex{--vertex1};
  path[current_vertex] = 0;

  while (current_vertex != vertex2 - 1 && current_vertex != -1) {
    visited[current_vertex] = true;

    auto adjacent = graph.AdjacentVertices(current_vertex + 1);

    for (size_t i = 0; i < adjacent.size(); ++i) {
      if (adjacent[i] > 0) {
        path[i] = std::min(path[i], path[current_vertex] + adjacent[i]);
      }
    }

    int nearest = -1;
    for (int i = 0; i < graph.Size(); ++i) {
      if (!visited[i] && (nearest == -1 || path[i] < path[nearest])) {
        nearest = i;
      }
    }

    current_vertex = nearest;
  }

  return path[--vertex2];
}

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(my::Graph &graph) {
  std::vector<std::vector<int>> result(graph.AdjacencyMatrix());
  int size = graph.Size();

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      for (int k = 0; k < size; ++k) {
        if (result[j][i] != 0 && result[i][k] != 0)
          result[j][k] = std::min(result[j][k], result[j][i] + result[i][k]);
      }
    }
  }

  return result;
}

}  // namespace my