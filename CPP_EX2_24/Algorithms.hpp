/**
 * in this project we will implement a graph using adjacency matrix
 * ecording to the README.md file we will implement the graph class and
 * relevant algorithms. the hole project will be test driven development refer
 * to the README.md file and the test files
 *
 * Author: Hagay Cohen : *****6180
 * Email: hagaycohen2@gmail.com
 */
#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Graph.hpp"

using namespace std;

namespace hagay {

const int INT_MAX = 2147483647;
const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

// a static functions class that will contain all the algorithms
class Algorithms {
   public:
    static int isConnected(Graph &graph);
    static string shortestPath(Graph &graph, size_t src, size_t dest);
    static string isContainsCycle(Graph &graph);
    static string isBipartite(Graph &graph);
    static string negativeCycle(Graph &graph);

   private:
    static vector<vector<int>> DFS(Graph &graph, size_t src);
    static vector<int> DFS_visit(Graph &graph, size_t src, vector<int> &visited);
    static void DFS_parents_visit(Graph &graph, size_t src, vector<int> &visited, vector<int> &parents);
    static vector<int> DFS_backEdge(Graph &graph, size_t src, vector<int> &visited, vector<int> &parents);
    static vector<int> BellmanFord(Graph &graph, size_t src);
};

class negativeCycleException : public exception {
   public:
    vector<int> cycle;

    negativeCycleException(vector<int> parents, int reveldvertex) {
        int current = reveldvertex;
        for (int i = 0; i < parents.size(); i++) {
            current = parents[(size_t)current];
        }
        int temp = current;
        do {
            cycle.push_back(current);
            current = parents[(size_t)current];
        } while (current != temp);
        cycle.push_back(temp);
    }
};

}  // namespace hagay