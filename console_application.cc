#include "console_application.h"

namespace my {

int ConsoleApplication::GetNumber() {
  int number;
  std::string str;

  while (true) {
    std::cout << "Input the vertex number >= 1 and <= " << graph_.Size()
              << ": ";
    getline(std::cin, str);

    try {
      number = stoi(str);
      if (number < 1 || number > graph_.Size()) {
        throw std::out_of_range("stoi");
      }
      break;
    } catch (const std::exception& e) {
      if (std::string(e.what()) == "stoi") {
        std::cout << "\e[31mInvalid the vertex number\e[0m\n";
      } else {
        std::cout << "\e[31m" << e.what() << "\e[0m" << std::endl;
      }
    }
  }

  return number;
}

int ConsoleApplication::GraphSize() { return graph_.Size(); }

void ConsoleApplication::LoadGraphFromFile() {
  std::string filename;
  std::cout << "Input file name: ";
  getline(std::cin, filename);

  try {
    graph_.LoadGraphFromFile(filename);
    std::cout << "\e[32mGraph loaded\n------------\n";
    std::cout << "Graph size: " << graph_.Size() << "\n\nAdjacency matrix:\n";
    graph_.Print();
    std::cout << "\e[0m\n";
  } catch (const std::exception& e) {
    std::cout << "\e[31m" << e.what() << "\e[0m" << std::endl;
  } catch (...) {
    std::cout << "\e[31mFile opening error\e[0m" << std::endl;
  }
}

void ConsoleApplication::ExportGraphToDot() {
  std::string filename;
  std::cout << "Input file name: ";
  getline(std::cin, filename);

  try {
    graph_.ExportGraphToDot(filename);
    std::cout << "\e[32mGraph exported to file with name " << filename;
    std::cout << "\e[0m\n";
  } catch (const std::exception& e) {
    std::cout << "\e[31m" << e.what() << "\e[0m" << std::endl;
  } catch (...) {
    std::cout << "\e[31mFile exporting error\e[0m" << std::endl;
  }
}

void ConsoleApplication::DepthFirstSearch() {
  std::cout << "What is the starting vertex?\n";
  int start_vertex = GetNumber();
  try {
    auto result = GraphAlgorithms::DepthFirstSearch(graph_, start_vertex);
    std::cout << "\e[32m\nDepth-first search in the graph from the vertex #"
              << start_vertex << '\n';
    for (auto vertex : result) {
      std::cout << vertex << ' ';
    }
    std::cout << "\e[0m\n";
  } catch (const std::exception& e) {
    std::cout << "\e[31m" << e.what() << "\e[0m" << std::endl;
  } catch (...) {
    std::cout << "\e[31mDepth-first searching error\e[0m" << std::endl;
  }
}

void ConsoleApplication::BreadthFirstSearch() {
  std::cout << "What is the starting vertex?\n";
  int start_vertex = GetNumber();
  try {
    std::cout << "\e[32m\nBreadth-first search in the graph from the vertex #"
              << start_vertex << '\n';
    auto result = GraphAlgorithms::BreadthFirstSearch(graph_, start_vertex);
    for (auto vertex : result) {
      std::cout << vertex << ' ';
    }
    std::cout << "\e[0m\n";
  } catch (const std::exception& e) {
    std::cout << "\e[31m" << e.what() << "\e[0m" << std::endl;
  } catch (...) {
    std::cout << "\e[31mBreadth-first searching error\e[0m" << std::endl;
  }
}

void ConsoleApplication::GetShortestPathBetweenVertices() {
  std::cout << "What is the starting vertex?\n";
  int vertex1 = GetNumber();
  std::cout << "What is the final vertex?\n";
  int vertex2 = GetNumber();
  try {
    auto result = GraphAlgorithms::GetShortestPathBetweenVertices(
        graph_, vertex1, vertex2);
    std::cout << "\e[32m\nThe shortest path between two vertices: #" << vertex1
              << " and #" << vertex2 << " (Dijkstra's algorithm): " << result
              << "\e[0m\n";
  } catch (const std::exception& e) {
    std::cout << "\e[31m" << e.what() << "\e[0m" << std::endl;
  } catch (...) {
    std::cout << "\e[31mDepth-first searching error\e[0m" << std::endl;
  }
}

void ConsoleApplication::GetShortestPathsBetweenAllVertices() {
  try {
    auto result = GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph_);
    std::cout << "\e[32m\nThe shortest paths between all pairs of vertices "
                 "(the Floyd-Warshall algorithm):\n";
    Graph::PrintAdjacencyMatrix(result);
    std::cout << "\e[0m";
  } catch (const std::exception& e) {
    std::cout << "\e[31m" << e.what() << "\e[0m" << std::endl;
  } catch (...) {
    std::cout << "\e[31mDepth-first searching error\e[0m" << std::endl;
  }
}

void ConsoleApplication::GetLeastSpanningTree() {
  try {
    auto result = GraphAlgorithms::GetLeastSpanningTree(graph_);
    std::cout << "\e[32m\nThe minimal spanning tree (Prim's algorithm):\n";
    Graph::PrintAdjacencyMatrix(result);
    std::cout << "\e[0m";
  } catch (const std::exception& e) {
    std::cout << "\e[31m" << e.what() << "\e[0m" << std::endl;
  } catch (...) {
    std::cout << "\e[31mDepth-first searching error\e[0m" << std::endl;
  }
}

void ConsoleApplication::SolveTravelingSalesmanProblem() {
  try {
    auto result = GraphAlgorithms::SolveTravelingSalesmanProblem(graph_);
    std::cout << "\e[32m\nThe traveling salesman's problem (the ant colony "
                 "algorithm):\n";
    if (result.distance == 2147483647) {
      std::cout << "\nNo path";
    } else {
      for (auto vertex : result.vertices) {
        std::cout << vertex << ' ';
      }
      std::cout << "\nLength: " << result.distance;
    }
    std::cout << "\e[0m\n";
  } catch (const std::exception& e) {
    std::cout << "\e[31m" << e.what() << "\e[0m" << std::endl;
  } catch (...) {
    std::cout << "\e[31mDepth-first searching error\e[0m" << std::endl;
  }
}

}  // namespace my

int main() {
  my::ConsoleApplication app;

  int input{-1};

  while (input != 0) {
    std::cout << "\n0 - Exit\n";
    std::cout << "1 - Load the original graph from a file\n";

    if (app.GraphSize() > 0) {
      std::cout << "2 - Traverse the graph in breadth\n";
      std::cout << "3 - Traverse the graph in depth\n";
      std::cout << "4 - Find the shortest path between any two vertices\n";
      std::cout
          << "5 - Find the shortest paths between all pairs of vertices\n";
      std::cout << "6 - Search for the minimum spanning tree in the graph\n";
      std::cout << "7 - Solve the Salesman problem\n";
      std::cout << "8 - Export the graph to a file in .dot format\n";
    }

    std::string input_str;
    std::cout << "\nInput number: ";
    getline(std::cin, input_str);

    try {
      input = stoi(input_str);
    } catch (...) {
      input = -1;
    }

    switch (input) {
      case 0:
        break;
      case 1:
        app.LoadGraphFromFile();
        break;
      default:
        if (app.GraphSize() <= 0) {
          input = -1;
        }
        break;
    }

    switch (input) {
      case 0 ... 1:
        break;
      case 2:
        app.BreadthFirstSearch();
        break;

      case 3:
        app.DepthFirstSearch();
        break;

      case 4:
        app.GetShortestPathBetweenVertices();
        break;

      case 5:
        app.GetShortestPathsBetweenAllVertices();
        break;

      case 6:
        app.GetLeastSpanningTree();
        break;

      case 7:
        app.SolveTravelingSalesmanProblem();
        break;

      case 8:
        app.ExportGraphToDot();
        break;

      default:
        std::cout << "\n\e[31mInvalid input\e[0m" << std::endl;
        break;
    }

    if (input != 0) {
      std::cout << "\nEnter to continue ";
      std::string str;
      getline(std::cin, str);
    }
  }

  return 0;
}
