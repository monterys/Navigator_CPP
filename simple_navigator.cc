#include "my_graph.h"
// #include "my_queue.h"
// #include "my_stack.h"

int main() {
  my::Graph graph("my_graph.txt");
  std::cout << "my::Graph graph(\"my_graph.txt\")\n"
            << graph.Size() << std::endl;
  graph.Print();

  my::Graph graphManual;
  graphManual.SetSize(3);
  std::cout << '\n' << "graphManual.SetSize(3)" << std::endl;
  std::cout << "size=" << graphManual.Size() << std::endl;
  graphManual.Print();

  graphManual(1, 1) = 5;
  graphManual(1, 2) = 12;
  graphManual(1, 3) = 9;
  graphManual(2, 2) = 45;
  graphManual(3, 3) = 98;
  std::cout << std::endl;
  graphManual.Print();

  graphManual.SetSize(5);
  std::cout << std::endl;
  std::cout << "graphManual.SetSize(5)\n";
  graphManual.Print();

  graphManual.DeleteNode(2);
  std::cout << std::endl;
  std::cout << "graphManual.DeleteNode(2);\n";
  graphManual.Print();

  graphManual(2, 2) = 23;
  std::cout << std::endl;
  std::cout << "graphManual(2,2) = 23;\n";
  graphManual.Print();

  graphManual.SetSize(2);
  std::cout << std::endl;
  std::cout << "graphManual.SetSize(2)\n";
  graphManual.Print();

  graphManual.AppendNode();
  std::cout << std::endl;
  std::cout << "graphManual.AppendNode()\n";
  graphManual.Print();

  graphManual.AppendNode();
  std::cout << std::endl;
  std::cout << "graphManual.AppendNode()\n";
  graphManual.Print();

  my::Graph graphManual1;
  graphManual1.AppendNode();
  std::cout << std::endl;
  std::cout << "graphManual1.AppendNode()\n";
  graphManual1.Print();
  std::cout << "size=" << graphManual1.Size() << std::endl;

  graph.ExportGraphToDot("my_graph.dot");
  auto matrix = graph.AdjacencyMatrix();
  for (int i = 0; i < graph.Size(); ++i) {
    for (int j = 0; j < graph.Size(); ++j) {
      std::cout << matrix[i][j] << '\t';
    }
    std::cout << std::endl;
  }
  // my::Stack stack;
  // stack.push(456);
  // stack.push(321);
  // std::cout << "\n\nstack.push(456); stack.push(321);" << std::endl;
  // std::cout << "stack.top()=" << stack.top() << std::endl;
  // std::cout << "stack.size()=" << stack.size() << std::endl;
  // std::cout << "stack.pop()=" << stack.pop() << std::endl;
  // std::cout << "stack.top()=" << stack.top() << std::endl;
  // std::cout << "stack.size()=" << stack.size() << std::endl;

  // my::Queue queue;
  // queue.push(789);
  // queue.push(123);
  // std::cout << "\n\nqueue.push(789); queue.push(123);" << std::endl;
  // std::cout << "queue.front()=" << queue.front() << std::endl;
  // std::cout << "queue.back()=" << queue.back() << std::endl;
  // std::cout << "queue.size()=" << queue.size() << std::endl;
  // std::cout << "queue.pop()=" << queue.pop() << std::endl;
  // std::cout << "queue.front()=" << queue.front() << std::endl;
  // std::cout << "queue.back()=" << queue.back() << std::endl;
  // std::cout << "queue.size()=" << queue.size() << std::endl;
}