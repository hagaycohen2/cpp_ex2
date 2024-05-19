#include "Algorithms.hpp"
#include "Graph.hpp"
#include "doctest.h"

using namespace std;

TEST_CASE("Test graph addition") {
    SUBCASE("Test graph addition") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        hagay::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
        g2.loadGraph(weightedGraph);
        hagay::Graph g3 = g1 + g2;
        vector<vector<int>> expectedGraph = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}};
        CHECK(g3.getMatrix() == expectedGraph);
    }
    SUBCASE("Test graph self addition") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        hagay::Graph g2;
        ;
        vector<vector<int>> weightedGraph = {
            {0, 33, 1},
            {33, 0, -5},
            {1, -5, 0}};
        g2.loadGraph(weightedGraph);
        g1 += g2;
        vector<vector<int>> expectedGraph = {
            {0, 34, 1},
            {34, 0, -4},
            {1, -4, 0}};
        CHECK(g1.getMatrix() == expectedGraph);
    }
    SUBCASE("Test graph onary addition") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, -3, 0},
            {1, 0, 7},
            {-6, 1, 0}};
        g1.loadGraph(graph);
        g1 = +g1;
        CHECK(g1.getMatrix() == graph);
    }
}

TEST_CASE("Test graph subtraction") {
    SUBCASE("Test graph subtraction") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 9, -5},
            {9, 0, 2},
            {-5, 2, 0}};
        g1.loadGraph(graph);
        hagay::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
        g2.loadGraph(weightedGraph);
        hagay::Graph g3 = g1 - g2;
        vector<vector<int>> expectedGraph = {
            {0, 8, -6},
            {8, 0, 0},
            {-6, 0, 0}};
        CHECK(g3.getMatrix() == expectedGraph);
        CHECK(g1.getEdges() == 6);
        CHECK(g3.getEdges() == 4);
    }
    SUBCASE("Test graph self subtraction") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 10, -6},
            {9, 0, 1},
            {0, 12, 0}};
        g1.loadGraph(graph);
        hagay::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 10, 6},
            {18, 0, 2},
            {7, 2, 0}};
        g2.loadGraph(weightedGraph);
        g1 -= g2;
        vector<vector<int>> expectedGraph = {
            {0, 0, -12},
            {-9, 0, -1},
            {-7, 10, 0}};
        CHECK(g1.getMatrix() == expectedGraph);
    }
    SUBCASE("Test graph onary negation") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 3, 0},
            {1, 0, 7},
            {6, 1, 0}};
        g1.loadGraph(graph);
        g1 = -g1;
        vector<vector<int>> expectedGraph = {
            {0, -3, 0},
            {-1, 0, -7},
            {-6, -1, 0}};
        CHECK(g1.getMatrix() == expectedGraph);

        hagay::Graph g2;
        vector<vector<int>> graph2 = {
            {0, -7, 0},
            {-3, 0, 18},
            {6, 2, 0}};
        g2.loadGraph(graph2);
        g2 = -g2;
        vector<vector<int>> expectedGraph2 = {
            {0, 7, 0},
            {3, 0, -18},
            {-6, -2, 0}};
        CHECK(g2.getMatrix() == expectedGraph2);

        hagay::Graph g3;
        vector<vector<int>> graph3 = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};
        g3.loadGraph(graph3);
        g1.loadGraph(graph);
        g3 = -g1;
        CHECK(g3.getMatrix() == expectedGraph);
        CHECK(g1.getMatrix() == graph);  // Check that g1 was not changed
    }
}
TEST_CASE("Test graph comparisons") {
    SUBCASE("Test graph comparison") {
        hagay::Graph g1, g2;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        g2.loadGraph(graph);
        CHECK(g1 == g2);

        hagay::Graph g3;
        vector<vector<int>> graph2 = {
            {0, -1, 0},
            {-19, 0, 1},
            {6, 0, 0}};
        g3.loadGraph(graph2);
        CHECK(g1 == g3);
    }
    SUBCASE("Test graph greater than") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        hagay::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {0, 2, 0}};
        g2.loadGraph(weightedGraph);
        CHECK(g2 > g1);

        hagay::Graph g3;
        vector<vector<int>> graph2 = {
            {0, -1},
            {6, 0}};
        g3.loadGraph(graph2);
        CHECK(g1 > g3);

        hagay::Graph g4;
        vector<vector<int>> graph3 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 0, 0}};
        g4.loadGraph(graph3);
        CHECK(g1 > g4);

        g2.loadGraph(graph);
        CHECK(!(g2 > g1));
    }
    SUBCASE("Test graph not equal") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        hagay::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {0, 2, 0}};
        g2.loadGraph(weightedGraph);
        CHECK(g2 != g1);

        hagay::Graph g3;
        vector<vector<int>> graph2 = {
            {0, -1},
            {6, 0}};
        g3.loadGraph(graph2);
        CHECK(g3 != g1);

        hagay::Graph g4;
        vector<vector<int>> graph3 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 0, 0}};
        g4.loadGraph(graph3);
        CHECK(g4 != g1);
    }
}

TEST_CASE("Test graph ++ , --") {
    SUBCASE("Test graph ++") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        g1++;
        vector<vector<int>> expectedGraph = {
            {0, 2, 1},
            {2, 0, 2},
            {1, 2, 0}};
        CHECK(g1.getMatrix() == expectedGraph);

        hagay::Graph g2;
        g2 = g1++;
      
        CHECK(g2.getMatrix() == expectedGraph);

        hagay::Graph g3;
        g3 = ++g2;

        CHECK(g3.getMatrix() == g2.getMatrix());
    }
    SUBCASE("Test graph --") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        g1--;
        vector<vector<int>> expectedGraph = {
            {0, 0, -1},
            {0, 0, 0},
            {-1, 0, 0}};
        CHECK(g1.getMatrix() == expectedGraph);

        hagay::Graph g2;
        g2 = g1--;
      
        CHECK(g2.getMatrix() == expectedGraph);

        hagay::Graph g3;
        g3 = --g2;

        CHECK(g3.getMatrix() == g2.getMatrix());
    }
}

TEST_CASE("Test graph multiplication by scalar") {
    SUBCASE("Test graph multiplication by scalar") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        hagay::Graph g2 = g1 * 3;
        vector<vector<int>> expectedGraph = {
            {0, 3, 0},
            {3, 0, 3},
            {0, 3, 0}};
        CHECK(g2.getMatrix() == expectedGraph);
    }
    SUBCASE("Test graph self multiplication by scalar") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 2},
            {0, 2, 0}};
        g1.loadGraph(graph);
        g1 = g1 * 3;
        vector<vector<int>> expectedGraph = {
            {0, 3, 0},
            {3, 0, 6},
            {0, 6, 0}};
        CHECK(g1.getMatrix() == expectedGraph);
    }
    SUBCASE("Test graph multiplication by scalar 0") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        hagay::Graph g2 = g1 * 0;
        vector<vector<int>> expectedGraph = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};
        CHECK(g2.getMatrix() == expectedGraph);
        CHECK(g1.getMatrix() == graph);  // Check that g1 was not changed
        CHECK(g2.getEdges() == 0);
    }
    SUBCASE("Test graph multiplication by scalar 1") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        hagay::Graph g2 = g1 * 1;
        CHECK(g2.getMatrix() == graph);
    }
    SUBCASE("Test graph multiplication by scalar -1") {
        hagay::Graph g1;
        vector<vector<int>> graph = {
            {0, -1, 0},
            {3, 0, 1},
            {0, 6, 0}};
        g1.loadGraph(graph);
        hagay::Graph g2 = g1 * -1;
        vector<vector<int>> expectedGraph = {
            {0, 1, 0},
            {-3, 0, -1},
            {0, -6, 0}};
        CHECK(g2.getMatrix() == expectedGraph);
        g1 = -g1;
        CHECK(g1.getMatrix() == expectedGraph);
    }
}
TEST_CASE("Test graphs multiplication") {
    hagay::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    hagay::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    hagay::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g4.getMatrix() == expectedGraph);
}

TEST_CASE("Invalid operations") {
    hagay::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    hagay::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1},
        {1, 1, 1, 0}};
    g2.loadGraph(weightedGraph);
    hagay::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g3.loadGraph(graph3);
    CHECK_THROWS(g3 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    hagay::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph4);
    CHECK_THROWS(g1 + g4);
}