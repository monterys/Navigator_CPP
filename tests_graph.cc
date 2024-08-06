#include "gtest/gtest.h"
#include "my_graph.h"

TEST(TestGraph, Test1) {
  my::Graph g;
  g.LoadGraphFromFile("my_graph.txt");

  EXPECT_EQ(g.Size(), 11);
  g.SetSize(3);
  EXPECT_EQ(g.Size(), 3);
  g.DeleteNode(2);
  EXPECT_EQ(g.Size(), 2);
  g.AppendNode();
  EXPECT_EQ(g.Size(), 3);
  g.SetSize(10);
  EXPECT_EQ(g.Size(), 10);
  EXPECT_EQ(g(10, 1), 0);
  EXPECT_EQ(g(10, 10), 0);
}

TEST(TestGraph, Test2) {
  my::Graph g("my_graph.txt");
  std::vector<int> adj_v = g.AdjacentVertices(2);
  std::vector<int> expected{29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12};
  EXPECT_EQ(adj_v, expected);
}

TEST(TestGraph, Test3) {
  my::Graph g("my_graph.txt");
  auto adj_m = g.AdjacencyMatrix();
  std::vector<std::vector<int> > expected{
      {0, 29, 20, 21, 16, 31, 100, 12, 4, 31, 18},
      {29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12},
      {20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
      {21, 29, 15, 0, 4, 12, 92, 12, 25, 13, 25},
      {16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
      {31, 40, 25, 12, 16, 0, 95, 24, 36, 3, 37},
      {100, 72, 81, 92, 94, 95, 0, 90, 101, 99, 84},
      {12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
      {4, 29, 23, 25, 20, 36, 101, 15, 0, 35, 18},
      {31, 41, 27, 13, 16, 3, 99, 25, 35, 0, 38},
      {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0}};
  EXPECT_EQ(adj_m, expected);
}

TEST(TestGraph, Test4) {
  my::Graph g("my_graph.txt");
  auto adj_m = g.AdjacentMatrix();
  std::vector<int> expected{
      0,  29, 20,  21, 16, 31, 100, 12, 4,  31, 18,  29, 0,  15, 29,  28,
      40, 72, 21,  29, 41, 12, 20,  15, 0,  15, 14,  25, 81, 9,  23,  27,
      13, 21, 29,  15, 0,  4,  12,  92, 12, 25, 13,  25, 16, 28, 14,  4,
      0,  16, 94,  9,  20, 16, 22,  31, 40, 25, 12,  16, 0,  95, 24,  36,
      3,  37, 100, 72, 81, 92, 94,  95, 0,  90, 101, 99, 84, 12, 21,  9,
      12, 9,  24,  90, 0,  15, 25,  13, 4,  29, 23,  25, 20, 36, 101, 15,
      0,  35, 18,  31, 41, 27, 13,  16, 3,  99, 25,  35, 0,  38, 18,  12,
      13, 25, 22,  37, 84, 13, 18,  38, 0};
  EXPECT_EQ(adj_m, expected);
}

TEST(TestGraph, Test5) {
  my::Graph g("my_graph_2.txt");
  std::string expected =
      "\n0\t4\t6\t10\t3\t\n4\t0\t3\t2\t0\t\n6\t3\t0\t1\t0\t\n10\t2\t1\t0\t0\t\n"
      "3\t0\t0\t0\t0\t\n";

  std::streambuf* cout_backup = std::cout.rdbuf();
  std::stringstream buffer;
  std::cout.rdbuf(buffer.rdbuf());
  my::Graph::PrintAdjacencyMatrix(g.AdjacencyMatrix());
  std::cout.rdbuf(cout_backup);

  EXPECT_EQ(buffer.str(), expected);
}

TEST(TestGraph, Test6) {
  my::Graph g("my_graph_2.txt");
  std::string expected =
      "\n0\t4\t6\t10\t3\t\n4\t0\t3\t2\t0\t\n6\t3\t0\t1\t0\t\n10\t2\t1\t0\t0\t\n"
      "3\t0\t0\t0\t0\t\n";

  std::streambuf* cout_backup = std::cout.rdbuf();
  std::stringstream buffer;
  std::cout.rdbuf(buffer.rdbuf());
  g.Print();
  std::cout.rdbuf(cout_backup);

  EXPECT_EQ(buffer.str(), expected);
}

TEST(TestGraph, Test7) {
  my::Graph g("my_graph_2.txt");
  std::string expected =
      "graph my_graph {\n\tv1 -- v2;\n\tv1 -- v3;\n\tv1 -- v4;\n\tv1 -- "
      "v5;\n\tv2 -- v1;\n\tv2 -- v3;\n\tv2 -- v4;\n\tv3 -- v1;\n\tv3 -- "
      "v2;\n\tv3 -- v4;\n\tv4 -- v1;\n\tv4 -- v2;\n\tv4 -- v3;\n\tv5 -- v1;\n}";

  g.ExportGraphToDot("my_graph_2.dot");
  std::ifstream file_dot("my_graph_2.dot");

  EXPECT_TRUE(file_dot.is_open());

  std::stringstream file_text;
  file_text << file_dot.rdbuf();
  EXPECT_EQ(file_text.str(), expected);
}

TEST(TestGraph, Test8) {
  my::Graph g("my_graph_2.txt");
  EXPECT_THROW(g(0, 0), std::out_of_range);
}

TEST(TestGraph, Test9) {
  EXPECT_THROW(my::Graph g("no_file"), std::runtime_error);
}

TEST(TestGraph, Test10) {
  EXPECT_THROW(my::Graph g("invalid_graph.txt"), std::out_of_range);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
