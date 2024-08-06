#include "gtest/gtest.h"
#include "my_graph_algorithms.h"

TEST(TestGraphAlgorithms, Test1) {
  my::Graph g("my_graph.txt");

  EXPECT_EQ(my::GraphAlgorithms::GetShortestPathBetweenVertices(g, 1, 4), 20);

  g.LoadGraphFromFile("my_graph_2.txt");

  EXPECT_EQ(my::GraphAlgorithms::GetShortestPathBetweenVertices(g, 1, 4), 6);
}

TEST(TestGraphAlgorithms, Test2) {
  my::Graph g("my_graph.txt");
  std::vector<std::vector<int> > expected{
      {0, 29, 20, 20, 16, 31, 100, 12, 4, 31, 18},
      {29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12},
      {20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
      {20, 29, 15, 0, 4, 12, 92, 12, 24, 13, 25},
      {16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
      {31, 40, 25, 12, 16, 0, 95, 24, 35, 3, 37},
      {100, 72, 81, 92, 94, 95, 0, 90, 101, 98, 84},
      {12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
      {4, 29, 23, 24, 20, 35, 101, 15, 0, 35, 18},
      {31, 41, 27, 13, 16, 3, 98, 25, 35, 0, 38},
      {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0}};

  EXPECT_EQ(my::GraphAlgorithms::GetShortestPathsBetweenAllVertices(g),
            expected);

  g.LoadGraphFromFile("my_graph_2.txt");
  expected = {{0, 4, 6, 6, 3},
              {4, 0, 3, 2, 0},
              {6, 3, 0, 1, 0},
              {6, 2, 1, 0, 0},
              {3, 0, 0, 0, 0}};

  EXPECT_EQ(my::GraphAlgorithms::GetShortestPathsBetweenAllVertices(g),
            expected);
}

TEST(TestGraphAlgorithms, Test3) {
  my::Graph g("my_graph.txt");
  std::vector<int> expected{5, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11};

  EXPECT_EQ(my::GraphAlgorithms::DepthFirstSearch(g, 5), expected);

  g.LoadGraphFromFile("my_graph_2.txt");
  expected = {2, 1, 5, 3, 4};

  EXPECT_EQ(my::GraphAlgorithms::DepthFirstSearch(g, 2), expected);
}

TEST(TestGraphAlgorithms, Test4) {
  my::Graph g("my_graph.txt");
  std::vector<int> expected{5, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11};

  EXPECT_EQ(my::GraphAlgorithms::BreadthFirstSearch(g, 5), expected);

  g.LoadGraphFromFile("my_graph_2.txt");
  expected = {2, 1, 3, 4, 5};

  EXPECT_EQ(my::GraphAlgorithms::BreadthFirstSearch(g, 2), expected);
}

TEST(TestGraphAlgorithms, Test5) {
  my::Graph g("my_graph.txt");
  std::vector<std::vector<int> > expected{
      {0, 0, 0, 0, 0, 0, 0, 12, 4, 0, 0}, {0, 0, 0, 0, 0, 0, 72, 0, 0, 0, 12},
      {0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0},  {0, 0, 0, 0, 4, 12, 0, 0, 0, 0, 0},
      {0, 0, 0, 4, 0, 0, 0, 9, 0, 0, 0},  {0, 0, 0, 12, 0, 0, 0, 0, 0, 3, 0},
      {0, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {12, 0, 9, 0, 9, 0, 0, 0, 0, 0, 13},
      {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  {0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
      {0, 12, 0, 0, 0, 0, 0, 13, 0, 0, 0}};

  EXPECT_EQ(my::GraphAlgorithms::GetLeastSpanningTree(g), expected);

  g.LoadGraphFromFile("my_graph_2.txt");
  expected = {{0, 4, 0, 0, 3},
              {4, 0, 0, 2, 0},
              {0, 0, 0, 1, 0},
              {0, 2, 1, 0, 0},
              {3, 0, 0, 0, 0}};

  EXPECT_EQ(my::GraphAlgorithms::GetLeastSpanningTree(g), expected);
}

TEST(TestGraphAlgorithms, Test6) {
  my::Graph g("my_graph.txt");
  size_t expected_size = 11;
  int expected_length = 253;

  auto result = my::GraphAlgorithms::SolveTravelingSalesmanProblem(g);
  EXPECT_EQ(result.vertices.size(), expected_size);
  EXPECT_EQ(result.distance, expected_length);
}
