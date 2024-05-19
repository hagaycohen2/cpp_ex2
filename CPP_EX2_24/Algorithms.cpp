/**
 * in this project we will implement a graph using adjacency matrix
 * ecording to the README.md file we will implement the graph class and
 * relevant algorithms. the hole project will be test driven development refer
 * to the README.md file and the test files
 *
 * Author: Hagay Cohen : *****6180
 * Email: hagaycohen2@gmail.com
 */

#include "Algorithms.hpp"

#include <iostream>
#include <vector>

#include "Graph.hpp"

using namespace std;
using namespace hagay;

/**
 * this function will visit all the vertices in the graph
 * the function will use DFS algorithm to visit all the vertices
 * the function will return the order of the vertices
 * */

vector<vector<int>> Algorithms::DFS(Graph &graph, size_t src) {
    vector<int> visited(graph.getVertices(), WHITE);
    vector<vector<int>> result;
    for (size_t i = 0; i < graph.getVertices(); i++) {
        if (visited[i] == WHITE) {
            result.push_back(DFS_visit(graph, i, visited));
        }
    }
    return result;
}

vector<int> Algorithms::DFS_visit(Graph &graph, size_t src,
                                  vector<int> &visited) {
    visited[src] = GRAY;
    vector<int> result;
    result.push_back(src);
    for (size_t i = 0; i < graph.getVertices(); i++) {
        if (graph.getMatrix()[src][i] != 0 && visited[i] == WHITE) {
            vector<int> temp = DFS_visit(graph, i, visited);
            result.insert(result.end(), temp.begin(), temp.end());
        }
    }
    visited[src] = BLACK;
    return result;
}

/**
 * this function will visit all the vertices in the graph
 * the function will use DFS algorithm to visit all the vertices
 * the function will return the parents of each vertex
 * */

void Algorithms::DFS_parents_visit(Graph &graph, size_t src, vector<int> &visited, vector<int> &parents) {
    visited[src] = GRAY;
    for (size_t i = 0; i < graph.getVertices(); i++) {
        if (graph.getMatrix()[src][i] != 0) {
            if (visited[i] == WHITE) {
                parents[i] = src;
                DFS_parents_visit(graph, i, visited, parents);
            }
        }
    }
    visited[src] = BLACK;
}


/**
 * this function will return the back edge in the graph
 * the function will use DFS algorithm to find the back edge
 * */

vector<int> Algorithms::DFS_backEdge(Graph &graph, size_t src, vector<int> &visited, vector<int> &parents) {
    visited[src] = GRAY;
    vector<int> result;
    for (size_t i = 0; i < graph.getVertices(); i++) {
        if (graph.getMatrix()[src][i] != 0) {
            if (visited[i] == GRAY && parents[src] != i) {
                result.push_back(i);
                result.push_back(src);
                return result;
            }
            if (visited[i] == WHITE) {
                vector<int> temp = DFS_backEdge(graph, i, visited, parents);
                if (!temp.empty()) {
                    return temp;
                }
            }
        }
    }
    visited[src] = BLACK;
    return result;
}

/**
 * this is a BellmanFord algorithm on steroids
 * the function will return the shortest path from src to all the other vertices
 * if there is a negative cycle the function will throw an exception
 * the exception will contain the cycle
 */
vector<int> Algorithms::BellmanFord(Graph &graph, size_t src) {
    vector<int> dist(graph.getVertices(), INT_MAX);
    vector<int> parents(graph.getVertices(), -1);
    dist[src] = 0;
    for (size_t i = 0; i < graph.getVertices() - 1; i++) {
        for (size_t j = 0; j < graph.getVertices(); j++) {
            for (size_t k = 0; k < graph.getVertices(); k++) {
                if (graph.getMatrix()[j][k] != 0) {
                    if (dist[j] + graph.getMatrix()[j][k] < dist[k]) {
                        dist[k] = dist[j] + graph.getMatrix()[j][k];
                        parents[k] = j;
                    }
                }
            }
        }
    }
    for (size_t j = 0; j < graph.getVertices(); j++) {
        for (size_t k = 0; k < graph.getVertices(); k++) {
            if (graph.getMatrix()[j][k] != 0) {
                if (dist[j] + graph.getMatrix()[j][k] < dist[k]) {
                    parents[k] = j;
                    throw negativeCycleException(parents, k);
                }
            }
        }
    }
    return parents;
}

/**
 * check if the graph is connected by using DFS tow times
 * first time from the first vertex and the second time from the last tree in
 * the first DFS result if the graph is connected the second DFS will return a
 * single tree
 */

int Algorithms::isConnected(Graph &graph) {
    vector<vector<int>> result = DFS(graph, 0);
    result = DFS(graph, (size_t)result[result.size() - 1][0]);
    if (result.size() == 1) {
        return 1;
    }
    return 0;
}

/**
 * this function will return the shortest path from src to dest
 * if there is no path the function will return -1
 * the function will use BellmanFord algorithm to calculate the shortest path
 * */

string Algorithms::shortestPath(Graph &graph, size_t src, size_t dest) {
    vector<int> parents;
    try {
        parents = BellmanFord(graph, src);
    } catch (negativeCycleException e) {
        return "The graph has a negative cycle";
    }
    if (src == dest) {
        return to_string(src);
    }
    if (parents[dest] == -1) {
        return "-1";
    }
    vector<int> path;
    size_t current = dest;
    while (current != src) {
        path.push_back(current);
        current = (size_t)parents[current];
    }
    path.push_back(src);
    string result = "";
    for (int i = path.size() - 1; i >= 0; i--) {
        result += to_string(path[(size_t)i]);
        if (i != 0) {
            result += "->";
        }
    }
    return result;
}

/**
 * this function will check if there is a cycle in the graph
 * the function will use the isContainsCycle_visit function
 * if there is a back edge the function will return the cycle path
 * */

string Algorithms::isContainsCycle(Graph &graph) {
    vector<int> visited(graph.getVertices(), WHITE);
    vector<int> parents(graph.getVertices(), -1);
    for (size_t i = 0; i < graph.getVertices(); i++) {
        if (visited[i] == WHITE) {
            DFS_parents_visit(graph, i, visited, parents);
        }
    }
    visited = vector<int>(graph.getVertices(), WHITE);
    for (size_t i = 0; i < graph.getVertices(); i++) {
        if (visited[i] == WHITE && parents[i] == -1) {
            vector<int> path = DFS_backEdge(graph, i, visited, parents);
            if (!path.empty()) {
                int start = path[0];
                int current = path[1];
                vector<int> temp = vector<int>();
                temp.push_back(start);
                while (current != start) {
                    temp.push_back(current);
                    current = parents[(size_t)current];
                }
                string cycle = "The cycle is: ";
                cycle += to_string(start);
                while (!temp.empty()) {
                    cycle += "->" + to_string(temp.back());
                    temp.pop_back();
                }
                return cycle;
            }
        }
    }
    return "0";
}

/**
 * this function will check if the graph is bipartite
 * the function will use BFS algorithm to color the vertices
 * if there is a vertex that has the same color as his neighbor
 * the function will return "0" (the graph is not bipartite)
 * else the function will return the two sets of the bipartite graph
 */

string Algorithms::isBipartite(Graph &graph) {
    vector<int> color(graph.getVertices(), WHITE);
    vector<int> queue;
    queue.push_back(0);
    color[0] = GRAY;
    while (!queue.empty()) {
        size_t current = (size_t)queue[0];
        queue.erase(queue.begin());
        for (size_t i = 0; i < graph.getVertices(); i++) {
            if (graph.getMatrix()[current][i] != 0) {
                if (color[i] == WHITE) {
                    if (color[current] == GRAY) {
                        color[i] = BLACK;
                    } else {
                        color[i] = GRAY;
                    }
                    queue.push_back(i);
                } else if (color[i] == color[current]) {
                    return "0";
                }
            }
        }
        if (queue.empty()) {
            for (size_t i = 0; i < graph.getVertices(); i++) {
                if (color[i] == WHITE) {
                    queue.push_back(i);
                    color[i] = GRAY;
                    i = graph.getVertices();
                }
            }
        }
    }
    string result = "The graph is bipartite: A={";
    for (size_t i = 0; i < color.size(); i++) {
        if (color[i] == GRAY) {
            result += to_string(i);
            if (i != color.size() - 1) {
                result += ", ";
            }
        }
    }
    if (result[result.size() - 1] == ' ') {
        result.pop_back();
        result.pop_back();
    }
    result += "}, B={";
    for (size_t i = 0; i < color.size(); i++) {
        if (color[i] == BLACK) {
            result += to_string(i);
            if (i != color.size() - 1) {
                result += ", ";
            }
        }
    }
    if (result[result.size() - 1] == ' ') {
        result.pop_back();
        result.pop_back();
    }
    result += "}";
    return result;
}

/**
 * this function will check if there is a negative cycle in the graph
 * the function will use BellmanFord algorithm
 * if there is a negative cycle the function will return the cycle path
 * else the function will print "there is no negative cycle" and return "-1"
 * */

string Algorithms::negativeCycle(Graph &graph) {
    vector<int> parents;
    try {
        parents = BellmanFord(graph, 0);
    } catch (negativeCycleException e) {
        string cycle = "The negative cycle is: ";
        for (int i = e.cycle.size() - 1; i >= 0; i--) {
            cycle += to_string(e.cycle[(size_t)i]);
            if (i != 0) {
                cycle += "->";
            }
        }
        return cycle;
    }
    return "0";
}
