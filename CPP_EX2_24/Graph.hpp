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
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using std::function;
using std::vector;

namespace hagay {
class Graph {
   private:
    vector<vector<int>> matrix;
    size_t vertices;
    size_t edges;

    void edgesUpdate(function<int(int)> func);
    void edgesUpdate(Graph& graph, function<int(int, int)> func);
    vector<vector<int>> matrixMult(vector<vector<int>>& a, vector<vector<int>>& b);

   public:
    // constructor
    Graph();

    void loadGraph(vector<vector<int>> graph);
    void printGraph();
    string toString();
    vector<vector<int>> getMatrix() { return this->matrix; };
    size_t getVertices() { return this->vertices; };
    size_t getEdges() { return this->edges; };

    // operators

    // Graph& operator=(const Graph &other);

    Graph& operator+() { return *this; };
    Graph operator+(const Graph& other);
    Graph& operator+=(const Graph& other) { return *this = *this + other; }
    Graph operator-() { return *this * -1; };
    Graph operator-(Graph& other) { return *this + -other; };
    Graph& operator-=(Graph& other) { return *this = *this - other; };

    bool operator>(Graph& other);
    bool operator<(Graph& other) { return other > *this; };
    bool operator==(Graph& other) { return !(*this > other) && !(*this < other); };
    bool operator!=(Graph& other) { return !(*this == other); };
    bool operator>=(Graph& other) { return *this > other || *this == other; };
    bool operator<=(Graph& other) { return *this < other || *this == other; };

    Graph operator++() {
        this->edgesUpdate([](int x) { return x + 1; });
        Graph temp = *this;
        return temp;
    };
    Graph operator++(int) {
        Graph temp = *this;
        *this = ++*this;
        return temp;
    };
    Graph operator--() {
        this->edgesUpdate([](int x) { return x - 1; });
        Graph temp = *this;
        return *this;
    };
    Graph operator--(int) {
        Graph temp = *this;
        *this = --*this;
        return temp;
    };

    Graph operator*(int scalar);
    Graph& operator*=(int scalar) { return *this = *this * scalar; };

    Graph operator*(Graph& other);

    friend ostream& operator<<(ostream& os, Graph& graph);
};
}  // namespace hagay