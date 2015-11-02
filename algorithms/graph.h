#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>
#include <map>
#include "node.h"

class Graph {
public:
    Graph(int v);
    Graph (std::string fileName);
    ~Graph();
    int V() { return v_; }
    int E() { return e_; }
    void addEdge(int v, int w);
    Node<int>* adj(int v);
    void toString();

    static int degree(Graph* g, int v);
    static int maxDegree(Graph* g);
    static int avgDegree(Graph* g);
    static int selfLoops(Graph* g);

private:
    int v_;
    int e_;
    Node<int>* adj_;
};


class DeepFirstSearch {
public:
    DeepFirstSearch(Graph* g, int s);
    ~DeepFirstSearch();
    bool marked(int v) { return marked_[v]; }
    int count() { return count_; }
private:
    bool* marked_;
    int count_;
    void dfs(Graph* g, int v);
};


class DeepFirstPaths {
public:
    DeepFirstPaths(Graph* g, int s);
    ~DeepFirstPaths();
    bool hasPathTo(int v) { return marked_[v]; }
    void pathTo(int v);
private:
    bool* marked_;
    int* edgeTo_;
    int s_;
    void dfs(Graph* g, int v);
};


class BreadthFirstPath {
public:
    BreadthFirstPath(Graph* g, int s);
    ~BreadthFirstPath();
    bool hasPathTo(int v) { return marked_[v]; }
    void pathTo(int v);
private:
    int s_;
    bool* marked_;
    int* edgeTo_;
    void bfs(Graph* g, int v);
};


class CCGraph {
public:
    CCGraph(Graph* g);
    ~CCGraph();
    bool connected(int v, int w);
    int count();
    int id(int v);
private:
    int count_;
    bool* marked_;
    int* id_;
    void dfs(Graph* g, int v);
};


class Cycle {
public:
    Cycle(Graph* g);
    ~Cycle();
    bool hasCycle() { return hasCycle_; }
private:
    bool hasCycle_;
    bool* marked_;
    void dfs(Graph* g, int v, int u);
};


class TwoColors {
public:
    TwoColors(Graph* g);
    ~TwoColors();
    bool isBipartite() { return isTwoColors_; }
private:
    bool isTwoColors_;
    bool* marked_;
    bool* colors_;
    void dfs(Graph* g, int v);
};


class SymbolGraph {
public:
    SymbolGraph (std::string fileName);
    ~SymbolGraph();
    Graph& G() const { return *g_; }
    bool contains(std::string key);
    int index(std::string key);
    std::string name(int index);
private:
  std::map< std::string, int >* st_;
  std::string* keys_;
  Graph* g_;
};


int testGraph(int argc, char *argv[]);

int testSymbolGraph(int argc, char *argv[]);

#endif // GRAPH_H
