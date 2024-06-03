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

    /**
     * update the edges of the graph by the given function
    */
    void edgesUpdate(function<int(int)> func);

    /**
     * update the edges of the graph by the given function and the given graph
    */
    void edgesUpdate(Graph& graph, function<int(int, int)> func);

    /**
     * multiply two matrices without tuching the diagonal
    */
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

    // unary + operator
    Graph& operator+() { return *this; };

    // binary + operator
    Graph operator+(const Graph& other);

    // self assignment + operator
    Graph& operator+=(const Graph& other) { return *this = *this + other; }

    // unary - operator
    Graph operator-() { return *this * -1; };

    // binary - operator
    Graph operator-(Graph& other) { return *this + -other; };

    // self assignment - operator
    Graph& operator-=(Graph& other) { return *this = *this - other; };

    // comparison operators


    bool operator>(Graph& other);

    bool operator<(Graph& other) { return other > *this; };

    bool operator==(Graph& other) { return !(*this > other) && !(*this < other); };

    bool operator!=(Graph& other) { return !(*this == other); };

    bool operator>=(Graph& other) { return *this > other || *this == other; };

    bool operator<=(Graph& other) { return *this < other || *this == other; };


    // increment and decrement operators

    Graph operator++() ; // prefix
       
    Graph operator++(int) ; // postfix
       
    Graph operator--() ; // prefix
       
    Graph operator--(int) ; // postfix
       

    // multiplication operators

    // scalar multiplication
    Graph operator*(int scalar);

    // self assignment scalar multiplication
    Graph& operator*=(int scalar) { return *this = *this * scalar; };

    // matrix multiplication of two graphs
    Graph operator*(Graph& other);


    // friend functions

    // overload the << operator to print the graph
    friend ostream& operator<<(ostream& os, Graph& graph);
};
}  // namespace hagay