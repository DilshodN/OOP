#include <gtest/gtest.h>
#include "../strategy.h"
#include "../dfs.h"
#include "../bfs.h"
#include "../find_path_vertex.h"
#include "../find_path_edge.h"
#include "../check_cyclic.h"
#include "../founder.h"

// проверка на ребра +
// Graph(vector<pair>) +
// разнести тесты +
std::vector<std::pair<Graph::vertex, Graph::vertex>> data_graph1 = {{1, 2}, {2, 1}, {1, 3},
                                                                   {3, 1}, {1, 4}, {4, 1},
                                                                   {4, 5}, {5, 4}, {4, 6},
                                                                   {6, 4}, {4, 7}, {7, 4},
                                                                   {6, 8}, {8, 6}, {6, 9},
                                                                   {9, 6}};

std::vector<std::pair<Graph::vertex, Graph::vertex>> data_graph2 = {{1, 2}, {1, 3}, {1, 4}, {4, 5},
                                                                    {4, 6}, {4, 7}, {6, 8}, {6, 9}};

std::vector<std::pair<Graph::vertex, Graph::vertex>> cyclic_graph1 = {{1, 2}, {1, 3}, {1, 4}, {4, 5},
                                                                     {4, 6}, {4, 7}, {6, 8}, {6, 9}};

std::vector<std::pair<Graph::vertex, Graph::vertex>> cyclic_graph2 = {{1, 2}, {1, 3}, {1, 4}, {4, 5},
                                                                      {4, 6}, {4, 7}, {6, 8}, {6, 9}, {1, 9}};

TEST(Graph, DoubleEdge){
    Graph g;
    g.add_edge(1, 2);
    g.add_edge(1, 2);
    EXPECT_EQ(g.count_of_vertices(), 2);
    g.add_edge(1, 3);
    EXPECT_EQ(g.count_of_vertices(), 3);
    g.add_edge(1, 3);
    EXPECT_EQ(g.count_of_vertices(), 3);

    std::vector<Graph::vertex> a1 =  {2, 3};
    std::vector<Graph::vertex> a2 =  {};
    std::vector<Graph::vertex> a3 = {4};

    EXPECT_EQ(g.adjacent_vertices(1), a1);
    EXPECT_EQ(g.adjacent_vertices(2), a2);
    EXPECT_EQ(g.adjacent_vertices(3), a2);
    g.add_edge(2, 4);
    EXPECT_EQ(g.adjacent_vertices(2), a3);
}

TEST(DFS, EmptyGraph) {
    const Graph g;
    std::shared_ptr<Traverser> tr = std::make_shared<FindPathToVertex>(4);
    std::shared_ptr<Strategy> st = std::make_shared<DFS>(g, tr);
//    s.execute(1);
    Founder f(g, st);
    f.find(1);
    EXPECT_TRUE(f.get_path().empty());
}

TEST(DFS, VisitNonExistentVertex) {
    Graph g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);

    std::shared_ptr<Traverser> tr = std::make_shared<FindPathToVertex>(4);
    std::shared_ptr<Strategy> st = std::make_shared<DFS>(g, tr);
    Founder f(g, st);
    f.find(1);
    EXPECT_TRUE(f.get_path().empty());
}

TEST (DFS, VisitExistentVertex) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr = std::make_shared<FindPathToVertex>(4);
    std::shared_ptr<Strategy> st = std::make_shared<DFS>(g, tr);
    Founder f(g, st);
    f.find(1);
    EXPECT_EQ(f.get_path().size(), 2);
    EXPECT_EQ(f.get_path().at(0), 1);
    EXPECT_EQ(f.get_path().at(1), 4);
}

TEST (DFS, VisitExistentVertex0) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr0 = std::make_shared<FindPathToVertex>(1);
    std::shared_ptr<Strategy> st0 = std::make_shared<DFS>(g, tr0);
    Founder f0(g, st0);
    f0.find(1);
    ASSERT_EQ(f0.get_path().size(), 1);
    EXPECT_EQ(f0.get_path().at(0), 1);
}

TEST (DFS, VisitExistentVertex1) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr1 = std::make_shared<FindPathToVertex>(2);
    std::shared_ptr<Strategy> st1 = std::make_shared<DFS>(g, tr1);
    Founder f1(g, st1);
    f1.find(1);
    ASSERT_EQ(f1.get_path().size(), 2);
    EXPECT_EQ(f1.get_path().at(0), 1);
    EXPECT_EQ(f1.get_path().at(1), 2);
}

TEST (DFS, VisitExistentVertex2) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr2 = std::make_shared<FindPathToVertex>(3);
    std::shared_ptr<Strategy> st2 = std::make_shared<DFS>(g, tr2);
    Founder f2(g, st2);
    f2.find(1);
    ASSERT_EQ(f2.get_path().size(), 2);
    EXPECT_EQ(f2.get_path().at(0), 1);
    EXPECT_EQ(f2.get_path().at(1), 3);
}

TEST (DFS, VisitExistentVertex3) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr3 = std::make_shared<FindPathToVertex>(5);
    std::shared_ptr<Strategy> st3 = std::make_shared<DFS>(g, tr3);
    Founder f3(g, st3);
    f3.find(1);
    ASSERT_EQ(f3.get_path().size(), 3);
    EXPECT_EQ(f3.get_path().at(0), 1);
    EXPECT_EQ(f3.get_path().at(1), 4);
    EXPECT_EQ(f3.get_path().at(2), 5);
}

TEST (DFS, VisitExistentVertex4) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr4 = std::make_shared<FindPathToVertex>(6);
    std::shared_ptr<Strategy> st4 = std::make_shared<DFS>(g, tr4);
    Founder f4(g, st4);
    f4.find(1);
    ASSERT_EQ(f4.get_path().size(), 3);
    EXPECT_EQ(f4.get_path().at(0), 1);
    EXPECT_EQ(f4.get_path().at(1), 4);
    EXPECT_EQ(f4.get_path().at(2), 6);
}

TEST (DFS, VisitExistentVertex5) {
    Graph g(data_graph1);

    std::shared_ptr<Traverser> tr5 = std::make_shared<FindPathToVertex>(7);
    std::shared_ptr<Strategy> st5 = std::make_shared<DFS>(g, tr5);
    Founder f5(g, st5);
    f5.find(1);
    ASSERT_EQ(f5.get_path().size(), 3);
    EXPECT_EQ(f5.get_path().at(0), 1);
    EXPECT_EQ(f5.get_path().at(1), 4);
    EXPECT_EQ(f5.get_path().at(2), 7);
}

TEST (DFS, VisitExistentVertex6) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr6 = std::make_shared<FindPathToVertex>(8);
    std::shared_ptr<Strategy> st6 = std::make_shared<DFS>(g, tr6);
    Founder f6(g, st6);
    f6.find(1);
    ASSERT_EQ(f6.get_path().size(), 4);
    EXPECT_EQ(f6.get_path().at(0), 1);
    EXPECT_EQ(f6.get_path().at(1), 4);
    EXPECT_EQ(f6.get_path().at(2), 6);
    EXPECT_EQ(f6.get_path().at(3), 8);
}

TEST (DFS, VisitExistentVertex7) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr7 = std::make_shared<FindPathToVertex>(9);
    std::shared_ptr<Strategy> st7 = std::make_shared<DFS>(g, tr7);
    Founder f7(g, st7);
    f7.find(1);
    ASSERT_EQ(f7.get_path().size(), 4);
    EXPECT_EQ(f7.get_path().at(0), 1);
    EXPECT_EQ(f7.get_path().at(1), 4);
    EXPECT_EQ(f7.get_path().at(2), 6);
    EXPECT_EQ(f7.get_path().at(3), 9);
}


TEST(DFS, VisitNonExistentEdge) {
    Graph g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    std::shared_ptr<Traverser> tr = std::make_shared<FindPathToEdge>(1, 4);
    std::shared_ptr<Strategy> st = std::make_shared<DFS>(g, tr);
    Founder f(g, st);
    f.find(1);
    EXPECT_TRUE(f.get_path().empty());
}

TEST(DFS, VisitExistentEdge) {
    Graph g(data_graph2);

    std::shared_ptr<Traverser> tr = std::make_shared<FindPathToEdge>(1, 4);
    std::shared_ptr<Strategy> st = std::make_shared<DFS>(g, tr);
    Founder f(g, st);
    f.find(1);
    ASSERT_EQ(f.get_path().size(), 2);
    EXPECT_EQ(f.get_path().at(0), 1);
    EXPECT_EQ(f.get_path().at(1), 4);
}
TEST(DFS, VisitExistentEdge1) {
    Graph g(data_graph2);

    std::shared_ptr<Traverser> tr1 = std::make_shared<FindPathToEdge>(1, 2);
    std::shared_ptr<Strategy> st1 = std::make_shared<DFS>(g, tr1);
    Founder f1(g, st1);
    f1.find(1);
    ASSERT_EQ(f1.get_path().size(), 2);
    EXPECT_EQ(f1.get_path().at(0), 1);
    EXPECT_EQ(f1.get_path().at(1), 2);
}
TEST(DFS, VisitExistentEdge2) {
    Graph g(data_graph2);
    std::shared_ptr<Traverser> tr2 = std::make_shared<FindPathToEdge>(1, 3);
    std::shared_ptr<Strategy> st2 = std::make_shared<DFS>(g, tr2);
    Founder f2(g, st2);
    f2.find(1);
    ASSERT_EQ(f2.get_path().size(), 2);
    EXPECT_EQ(f2.get_path().at(0), 1);
    EXPECT_EQ(f2.get_path().at(1), 3);
}
TEST(DFS, VisitExistentEdge3) {
    Graph g(data_graph2);

    std::shared_ptr<Traverser> tr3 = std::make_shared<FindPathToEdge>(4, 5);
    std::shared_ptr<Strategy> st3 = std::make_shared<DFS>(g, tr3);
    Founder f3(g, st3);
    f3.find(1);
    ASSERT_EQ(f3.get_path().size(), 3);
    EXPECT_EQ(f3.get_path().at(0), 1);
    EXPECT_EQ(f3.get_path().at(1), 4);
    EXPECT_EQ(f3.get_path().at(2), 5);
}
TEST(DFS, VisitExistentEdge4) {
    Graph g(data_graph2);

    std::shared_ptr<Traverser> tr4 = std::make_shared<FindPathToEdge>(4, 6);
    std::shared_ptr<Strategy> st4 = std::make_shared<DFS>(g, tr4);
    Founder f4(g, st4);
    f4.find(1);
    ASSERT_EQ(f4.get_path().size(), 3);
    EXPECT_EQ(f4.get_path().at(0), 1);
    EXPECT_EQ(f4.get_path().at(1), 4);
    EXPECT_EQ(f4.get_path().at(2), 6);
}
TEST(DFS, VisitExistentEdge5) {
    Graph g(data_graph2);

    std::shared_ptr<Traverser> tr5 = std::make_shared<FindPathToEdge>(4, 7);
    std::shared_ptr<Strategy> st5 = std::make_shared<DFS>(g, tr5);
    Founder f5(g, st5);
    f5.find(1);
    ASSERT_EQ(f5.get_path().size(), 3);
    EXPECT_EQ(f5.get_path().at(0), 1);
    EXPECT_EQ(f5.get_path().at(1), 4);
    EXPECT_EQ(f5.get_path().at(2), 7);
}
TEST(DFS, VisitExistentEdge6) {
    Graph g(data_graph2);
    std::shared_ptr<Traverser> tr6 = std::make_shared<FindPathToEdge>(6, 8);
    std::shared_ptr<Strategy> st6 = std::make_shared<DFS>(g, tr6);
    Founder f6(g, st6);
    f6.find(1);
    ASSERT_EQ(f6.get_path().size(), 4);
    EXPECT_EQ(f6.get_path().at(0), 1);
    EXPECT_EQ(f6.get_path().at(1), 4);
    EXPECT_EQ(f6.get_path().at(2), 6);
    EXPECT_EQ(f6.get_path().at(3), 8);
}

TEST(DFS, VisitExistentEdge7) {
    Graph g(data_graph2);
    std::shared_ptr<Traverser> tr7 = std::make_shared<FindPathToEdge>(6, 9);
    std::shared_ptr<Strategy> st7 = std::make_shared<DFS>(g, tr7);
    Founder f7(g, st7);
    f7.find(1);
    ASSERT_EQ(f7.get_path().size(), 4);
    EXPECT_EQ(f7.get_path().at(0), 1);
    EXPECT_EQ(f7.get_path().at(1), 4);
    EXPECT_EQ(f7.get_path().at(2), 6);
    EXPECT_EQ(f7.get_path().at(3), 9);
}

TEST(DFS, CyclicGraph) {
    Graph g(cyclic_graph1);


    std::shared_ptr<Traverser> tr = std::make_shared<CheckCyclic>();
    std::shared_ptr<Strategy> st = std::make_shared<DFS>(g, tr);
    Founder f(g, st);
    f.find(1);
    EXPECT_FALSE(f.is_cyclic());

    g.add_edge(4, 8);
    f.find(1);
    EXPECT_TRUE(f.is_cyclic());

    Graph g1(cyclic_graph2);

    std::shared_ptr<Strategy> st1 = std::make_shared<DFS>(g, tr);
    Founder f1(g, st1);
    EXPECT_TRUE(f1.is_cyclic());
}

TEST(BFS, EmptyGraph) {
    const Graph g;
    std::shared_ptr<Traverser> tr = std::make_shared<FindPathToVertex>(4);
    std::shared_ptr<Strategy> st = std::make_shared<BFS>(g, tr);
//    s.execute(1);
    Founder f(g, st);
    f.find(1);
    EXPECT_TRUE(f.get_path().empty());
}

TEST(BFS, VisitNonExistentVertex) {
    Graph g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);

    std::shared_ptr<Traverser> tr = std::make_shared<FindPathToVertex>(4);
    std::shared_ptr<Strategy> st = std::make_shared<BFS>(g, tr);
    Founder f(g, st);
    f.find(1);
    EXPECT_TRUE(f.get_path().empty());
}

TEST (BFS, VisitExistentVertex) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr = std::make_shared<FindPathToVertex>(4);
    std::shared_ptr<Strategy> st = std::make_shared<BFS>(g, tr);
    Founder f(g, st);
    f.find(1);
    EXPECT_EQ(f.get_path().size(), 2);
    EXPECT_EQ(f.get_path().at(0), 1);
    EXPECT_EQ(f.get_path().at(1), 4);
}

TEST (BFS, VisitExistentVertex0) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr0 = std::make_shared<FindPathToVertex>(1);
    std::shared_ptr<Strategy> st0 = std::make_shared<BFS>(g, tr0);
    Founder f0(g, st0);
    f0.find(1);
    ASSERT_EQ(f0.get_path().size(), 1);
    EXPECT_EQ(f0.get_path().at(0), 1);
}

TEST (BFS, VisitExistentVertex1) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr1 = std::make_shared<FindPathToVertex>(2);
    std::shared_ptr<Strategy> st1 = std::make_shared<BFS>(g, tr1);
    Founder f1(g, st1);
    f1.find(1);
    ASSERT_EQ(f1.get_path().size(), 2);
    EXPECT_EQ(f1.get_path().at(0), 1);
    EXPECT_EQ(f1.get_path().at(1), 2);
}

TEST (BFS, VisitExistentVertex2) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr2 = std::make_shared<FindPathToVertex>(3);
    std::shared_ptr<Strategy> st2 = std::make_shared<BFS>(g, tr2);
    Founder f2(g, st2);
    f2.find(1);
    ASSERT_EQ(f2.get_path().size(), 2);
    EXPECT_EQ(f2.get_path().at(0), 1);
    EXPECT_EQ(f2.get_path().at(1), 3);
}

TEST (BFS, VisitExistentVertex3) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr3 = std::make_shared<FindPathToVertex>(5);
    std::shared_ptr<Strategy> st3 = std::make_shared<BFS>(g, tr3);
    Founder f3(g, st3);
    f3.find(1);
    ASSERT_EQ(f3.get_path().size(), 3);
    EXPECT_EQ(f3.get_path().at(0), 1);
    EXPECT_EQ(f3.get_path().at(1), 4);
    EXPECT_EQ(f3.get_path().at(2), 5);
}

TEST (BFS, VisitExistentVertex4) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr4 = std::make_shared<FindPathToVertex>(6);
    std::shared_ptr<Strategy> st4 = std::make_shared<BFS>(g, tr4);
    Founder f4(g, st4);
    f4.find(1);
    ASSERT_EQ(f4.get_path().size(), 3);
    EXPECT_EQ(f4.get_path().at(0), 1);
    EXPECT_EQ(f4.get_path().at(1), 4);
    EXPECT_EQ(f4.get_path().at(2), 6);
}

TEST (BFS, VisitExistentVertex5) {
    Graph g(data_graph1);

    std::shared_ptr<Traverser> tr5 = std::make_shared<FindPathToVertex>(7);
    std::shared_ptr<Strategy> st5 = std::make_shared<BFS>(g, tr5);
    Founder f5(g, st5);
    f5.find(1);
    ASSERT_EQ(f5.get_path().size(), 3);
    EXPECT_EQ(f5.get_path().at(0), 1);
    EXPECT_EQ(f5.get_path().at(1), 4);
    EXPECT_EQ(f5.get_path().at(2), 7);
}

TEST (BFS, VisitExistentVertex6) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr6 = std::make_shared<FindPathToVertex>(8);
    std::shared_ptr<Strategy> st6 = std::make_shared<BFS>(g, tr6);
    Founder f6(g, st6);
    f6.find(1);
    ASSERT_EQ(f6.get_path().size(), 4);
    EXPECT_EQ(f6.get_path().at(0), 1);
    EXPECT_EQ(f6.get_path().at(1), 4);
    EXPECT_EQ(f6.get_path().at(2), 6);
    EXPECT_EQ(f6.get_path().at(3), 8);
}

TEST (BFS, VisitExistentVertex7) {
    Graph g(data_graph1);
    std::shared_ptr<Traverser> tr7 = std::make_shared<FindPathToVertex>(9);
    std::shared_ptr<Strategy> st7 = std::make_shared<BFS>(g, tr7);
    Founder f7(g, st7);
    f7.find(1);
    ASSERT_EQ(f7.get_path().size(), 4);
    EXPECT_EQ(f7.get_path().at(0), 1);
    EXPECT_EQ(f7.get_path().at(1), 4);
    EXPECT_EQ(f7.get_path().at(2), 6);
    EXPECT_EQ(f7.get_path().at(3), 9);
}


TEST(BFS, VisitNonExistentEdge) {
    Graph g;
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    std::shared_ptr<Traverser> tr = std::make_shared<FindPathToEdge>(1, 4);
    std::shared_ptr<Strategy> st = std::make_shared<BFS>(g, tr);
    Founder f(g, st);
    f.find(1);
    EXPECT_TRUE(f.get_path().empty());
}

TEST(BFS, VisitExistentEdge) {
    Graph g(data_graph2);

    std::shared_ptr<Traverser> tr = std::make_shared<FindPathToEdge>(1, 4);
    std::shared_ptr<Strategy> st = std::make_shared<BFS>(g, tr);
    Founder f(g, st);
    f.find(1);
    ASSERT_EQ(f.get_path().size(), 2);
    EXPECT_EQ(f.get_path().at(0), 1);
    EXPECT_EQ(f.get_path().at(1), 4);
}
TEST(BFS, VisitExistentEdge1) {
    Graph g(data_graph2);

    std::shared_ptr<Traverser> tr1 = std::make_shared<FindPathToEdge>(1, 2);
    std::shared_ptr<Strategy> st1 = std::make_shared<BFS>(g, tr1);
    Founder f1(g, st1);
    f1.find(1);
    ASSERT_EQ(f1.get_path().size(), 2);
    EXPECT_EQ(f1.get_path().at(0), 1);
    EXPECT_EQ(f1.get_path().at(1), 2);
}
TEST(BFS, VisitExistentEdge2) {
    Graph g(data_graph2);
    std::shared_ptr<Traverser> tr2 = std::make_shared<FindPathToEdge>(1, 3);
    std::shared_ptr<Strategy> st2 = std::make_shared<BFS>(g, tr2);
    Founder f2(g, st2);
    f2.find(1);
    ASSERT_EQ(f2.get_path().size(), 2);
    EXPECT_EQ(f2.get_path().at(0), 1);
    EXPECT_EQ(f2.get_path().at(1), 3);
}
TEST(BFS, VisitExistentEdge3) {
    Graph g(data_graph2);

    std::shared_ptr<Traverser> tr3 = std::make_shared<FindPathToEdge>(4, 5);
    std::shared_ptr<Strategy> st3 = std::make_shared<BFS>(g, tr3);
    Founder f3(g, st3);
    f3.find(1);
    ASSERT_EQ(f3.get_path().size(), 3);
    EXPECT_EQ(f3.get_path().at(0), 1);
    EXPECT_EQ(f3.get_path().at(1), 4);
    EXPECT_EQ(f3.get_path().at(2), 5);
}
TEST(BFS, VisitExistentEdge4) {
    Graph g(data_graph2);

    std::shared_ptr<Traverser> tr4 = std::make_shared<FindPathToEdge>(4, 6);
    std::shared_ptr<Strategy> st4 = std::make_shared<BFS>(g, tr4);
    Founder f4(g, st4);
    f4.find(1);
    ASSERT_EQ(f4.get_path().size(), 3);
    EXPECT_EQ(f4.get_path().at(0), 1);
    EXPECT_EQ(f4.get_path().at(1), 4);
    EXPECT_EQ(f4.get_path().at(2), 6);
}
TEST(BFS, VisitExistentEdge5) {
    Graph g(data_graph2);

    std::shared_ptr<Traverser> tr5 = std::make_shared<FindPathToEdge>(4, 7);
    std::shared_ptr<Strategy> st5 = std::make_shared<BFS>(g, tr5);
    Founder f5(g, st5);
    f5.find(1);
    ASSERT_EQ(f5.get_path().size(), 3);
    EXPECT_EQ(f5.get_path().at(0), 1);
    EXPECT_EQ(f5.get_path().at(1), 4);
    EXPECT_EQ(f5.get_path().at(2), 7);
}
TEST(BFS, VisitExistentEdge6) {
    Graph g(data_graph2);
    std::shared_ptr<Traverser> tr6 = std::make_shared<FindPathToEdge>(6, 8);
    std::shared_ptr<Strategy> st6 = std::make_shared<BFS>(g, tr6);
    Founder f6(g, st6);
    f6.find(1);
    ASSERT_EQ(f6.get_path().size(), 4);
    EXPECT_EQ(f6.get_path().at(0), 1);
    EXPECT_EQ(f6.get_path().at(1), 4);
    EXPECT_EQ(f6.get_path().at(2), 6);
    EXPECT_EQ(f6.get_path().at(3), 8);
}

TEST(BFS, VisitExistentEdge7) {
    Graph g(data_graph2);
    std::shared_ptr<Traverser> tr7 = std::make_shared<FindPathToEdge>(6, 9);
    std::shared_ptr<Strategy> st7 = std::make_shared<BFS>(g, tr7);
    Founder f7(g, st7);
    f7.find(1);
    ASSERT_EQ(f7.get_path().size(), 4);
    EXPECT_EQ(f7.get_path().at(0), 1);
    EXPECT_EQ(f7.get_path().at(1), 4);
    EXPECT_EQ(f7.get_path().at(2), 6);
    EXPECT_EQ(f7.get_path().at(3), 9);
}

TEST(BFS, CyclicGraph) {
    Graph g(cyclic_graph1);


    std::shared_ptr<Traverser> tr = std::make_shared<CheckCyclic>();
    std::shared_ptr<Strategy> st = std::make_shared<BFS>(g, tr);
    Founder f(g, st);
    f.find(1);
    EXPECT_FALSE(f.is_cyclic());

    g.add_edge(4, 8);
    f.find(1);
    EXPECT_TRUE(f.is_cyclic());

    Graph g1(cyclic_graph2);

    std::shared_ptr<Strategy> st1 = std::make_shared<BFS>(g, tr);
    Founder f1(g, st1);
    EXPECT_TRUE(f1.is_cyclic());
}
