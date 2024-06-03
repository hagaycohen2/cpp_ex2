/**
 * in this project we will implement a graph using adjacency matrix
 * ecording to the README.md file we will implement the graph class and
 * relevant algorithms. the hole project will be test driven development refer
 * to the README.md file and the test files
 *
 * Author: Hagay Cohen : *****6180
 * Email: hagaycohen2@gmail.com
 */

#include "Graph.hpp"

#include <iostream>

using namespace std;
using namespace hagay;

// constructor
Graph::Graph() {
    this->vertices = 0;
    this->edges = 0;
};

/**
 * initialize the graph with the given matrix
 * if number of rows and columns are not equal the function will throw an
 * exception if the matrix is not symmetric and the graph was initialized as
 * undirected the function will throw an exception if the diagonal of the matrix
 * is not zero the function will throw an exception
 * */
void Graph::loadGraph(vector<vector<int>> graph) {
    for (size_t i = 0; i < graph.size(); i++) {
        if (graph.size() != graph[i].size()) {
            throw invalid_argument("The graph matrix is invalid");
        }
    }
    this->matrix = graph;
    this->vertices = graph.size();
    this->edges = 0;
    for (size_t i = 0; i < graph.size(); i++) {
        for (size_t j = 0; j < graph[i].size(); j++) {
            if (i == j) {
                if (graph[i][j] != 0) {
                    throw invalid_argument("The graph matrix is invalid");
                }
            }
            if (graph[i][j] != 0) {
                this->edges++;
            }
        }
    }
}

/**
 * print the graph
 * */
void Graph::printGraph() {
    cout << "Graph with " << this->vertices << " vertices and " << this->edges
         << " edges." << endl;
    for (size_t i = 0; i < this->matrix.size(); i++) {
        for (size_t j = 0; j < this->matrix[i].size(); j++) {
            cout << this->matrix[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * return the graph as a string
 * */

string Graph::toString() {
    string str = "Graph with " + to_string(this->vertices) + " vertices and " +
                 to_string(this->edges) + " edges.\n";
    for (size_t i = 0; i < this->matrix.size(); i++) {
        for (size_t j = 0; j < this->matrix[i].size(); j++) {
            str += to_string(this->matrix[i][j]) + " ";
        }
        str += "\n";
    }
    return str;
}

/**
 * update the edges of the graph using the given function
 * */
void Graph::edgesUpdate(function<int(int)> func) {
    this->edges = 0;
    for (size_t i = 0; i < this->matrix.size(); i++) {
        for (size_t j = 0; j < this->matrix[i].size(); j++) {
            if (i != j) {
                this->matrix[i][j] = func(this->matrix[i][j]);
                if (this->matrix[i][j] != 0) {
                    this->edges++;
                }
            }
        }
    }
}

/**
 * update the edges of the graph using the given function and the given graph
 * */
void Graph::edgesUpdate(Graph &graph, function<int(int, int)> func) {
    this->edges = 0;
    for (size_t i = 0; i < this->matrix.size(); i++) {
        for (size_t j = 0; j < this->matrix[i].size(); j++) {
            if (i != j) {
                this->matrix[i][j] = func(this->matrix[i][j], graph.matrix[i][j]);
                if (this->matrix[i][j] != 0) {
                    this->edges++;
                }
            }
        }
    }
}

/**
 * multiply two matrices
 * */
vector<vector<int>> Graph::matrixMult(vector<vector<int>> &a, vector<vector<int>> &b) {
    vector<vector<int>> result(a.size(), vector<int>(b[0].size(), 0));
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < b[0].size(); j++) {
            for (size_t k = 0; k < a[0].size(); k++) {
                if (i != j) {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }
    return result;
}

/**
 * overload the + operator to add two graphs
 * if the graphs have different number of vertices the function will throw an exception
 * return the new graph
 * */

Graph Graph::operator+(const Graph &other) {
    if (this->vertices != other.vertices) {
        throw invalid_argument("The graphs have different number of vertices");
    }
    vector<vector<int>> newMatrix = other.matrix;
    Graph newGraph;
    newGraph.loadGraph(newMatrix);
    newGraph.edgesUpdate(*this, [](int a, int b) { return a + b; });
    return newGraph;
}

/**
 * overload the > operator to compare two graphs
 * if all the edges and vertices of B exist in A and A has more edges than B return true (A > B)
 * else if A has more edges than B return true (A > B)
 * else if A has the same number of edges as B and A has more vertices than B return true (A > B)
 * else return false (A <= B)
 * */

bool Graph::operator>(Graph &other) {
    if (this->vertices == other.vertices) {
        int sameEdges = 0;
        for (size_t i = 0; i < this->matrix.size(); i++) {
            for (size_t j = 0; j < this->matrix[i].size(); j++) {
                if (this->matrix[i][j] == other.matrix[i][j] && this->matrix[i][j] != 0) {
                    sameEdges++;
                }
            }
        }
        if (sameEdges == other.edges && this->edges > other.edges) {
            return true;
        }
    }
    if (this->edges > other.edges) {
        return true;
    }
    if (this->edges == other.edges && this->vertices > other.vertices) {
        return true;
    }
    return false;
}


 Graph Graph::operator++() { // prefix
        this->edgesUpdate([](int x) { return x + 1; });
        Graph temp = *this;
        return temp;
    };
    Graph Graph::operator++(int) { // postfix
        Graph temp = *this;
        *this = ++*this;
        return temp;
    };
    Graph Graph::operator--() { // prefix
        this->edgesUpdate([](int x) { return x - 1; });
        Graph temp = *this;
        return *this;
    };
    Graph Graph::operator--(int) { // postfix
        Graph temp = *this;
        *this = --*this;
        return temp;
    };


/**
 * overload the * operator to multiply the graph by a scalar
 * return the new graph
 * */

Graph Graph::operator*(int scalar) {
    vector<vector<int>> newMatrix = this->matrix;
    Graph newGraph;
    newGraph.loadGraph(newMatrix);
    newGraph.edgesUpdate([scalar](int a) { return a * scalar; });
    return newGraph;
}

/**
 * overload the * operator to multiply two graphs
 * if the graphs have different number of vertices the function will throw an exception
 * else, multiply the graphs by matrix multiplication
 * return the new graph containing the result
 * */

Graph Graph::operator*(Graph &other) {
    if (this->vertices != other.vertices) {
        throw invalid_argument("The graphs have different number of vertices");
    }
    vector<vector<int>> newMatrix = matrixMult(this->matrix, other.matrix);
    Graph newGraph;
    newGraph.loadGraph(newMatrix);
    return newGraph;
}

/**
 * overload the << operator to print the graph
 * */

ostream &hagay::operator<<(ostream &os, Graph &graph) {
    if (graph.getVertices() == 0 && graph.getEdges() == 0) {
        os << "Graph is empty" << endl;
        return os;
    }
    os << "Graph with " << graph.getVertices() << " vertices and " << graph.getEdges() << " edges." << endl;
    for (size_t i = 0; i < graph.getMatrix().size(); i++) {
        for (size_t j = 0; j < graph.getMatrix()[i].size(); j++) {
            os << graph.getMatrix()[i][j] << " ";
        }
        os << endl;
    }
    return os;
}