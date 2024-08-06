#include "my_graph.h"

namespace my {

Graph::Graph() : size_(0) {}

Graph::Graph(std::string filename) { LoadGraphFromFile(filename); }

int& Graph::operator()(int i, int j) {
  if (--i < 0 || --j < 0 || i >= size_ || j >= size_) {
    throw std::out_of_range("Incorrect input, index of matrix is out of range");
  }
  return matrix_[i * size_ + j];
}

int Graph::Size() { return size_; }

void Graph::SetSize(int size) {
  while (size_ > size) {
    DeleteNode(size_);
  }

  while (size_ < size) {
    AppendNode();
  }
}

void Graph::DeleteNode(int number) {
  --number;
  std::vector<int> new_matrix;

  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (i != number && j != number) {
        new_matrix.push_back(matrix_[i * size_ + j]);
      }
    }
  }

  matrix_ = std::move(new_matrix);
  --size_;
}

void Graph::AppendNode() {
  std::vector<int> new_matrix;

  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      new_matrix.push_back(matrix_[i * size_ + j]);
    }
    new_matrix.push_back(0);
  }
  ++size_;
  for (int i = 0; i < size_; ++i) {
    new_matrix.push_back(0);
  }
  matrix_ = std::move(new_matrix);
}

void Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream graph_file(filename);

  if (!graph_file.is_open()) {
    throw std::runtime_error("File not found");
  }

  graph_file >> size_;

  if (size_ <= 0) {
    throw std::out_of_range("Incorrect file, size value must be > 0");
  }

  matrix_.clear();
  while (!graph_file.eof()) {
    graph_file >> matrix_.emplace_back();
  }

  matrix_.resize(size_ * size_);
}

void Graph::ExportGraphToDot(std::string filename) {
  std::ofstream dot_file(filename);
  if (!dot_file.is_open()) throw std::runtime_error("Writing error");

  dot_file << "graph my_graph {\n";

  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (matrix_[i * size_ + j] != 0) {
        dot_file << "\tv" << i + 1 << " -- " << 'v' << j + 1 << ";\n";
      }
    }
  }

  dot_file << "}";
}

void Graph::Print() {
  std::cout << '\n';
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      std::cout << matrix_[i * size_ + j] << '\t';
    }
    std::cout << '\n';
  }
}

std::vector<int> Graph::AdjacentVertices(int vertex) {
  auto begin = matrix_.begin() + size_ * --vertex;
  return std::vector<int>(begin, begin + size_);
}

std::vector<int> Graph::AdjacentMatrix() { return matrix_; }

std::vector<std::vector<int> > Graph::AdjacencyMatrix() {
  std::vector<std::vector<int> > result;
  for (int i = 0; i < size_; ++i) {
    auto begin = matrix_.begin() + i * size_;
    result.push_back(std::vector<int>(begin, begin + size_));
  }
  return result;
}

void Graph::PrintAdjacencyMatrix(std::vector<std::vector<int> > matrix) {
  std::cout << '\n';
  for (auto line : matrix) {
    for (auto value : line) {
      std::cout << value << '\t';
    }
    std::cout << '\n';
  }
}

}  // namespace my