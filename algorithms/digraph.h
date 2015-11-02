#ifndef DIGRAPH_H
#define DIGRAPH_H
#include <iostream>
#include <stack>
#include <queue>
#include "node.h"

class DiGraph {
public:
    DiGraph(int v);
    DiGraph(std::string fileName);
    ~DiGraph();
    int V() { return v_; }
    int E() { return e_; }
    void addEdge(int v, int w);
    Node<int>* adj(int v);
    void toString();

    static int degree(DiGraph* g, int v);
    static int maxDegree(DiGraph* g);
    static int avgDegree(DiGraph* g);
    static int selfLoops(DiGraph* g);
    static DiGraph* reverse(DiGraph* g);

private:
    int v_;
    int e_;
    Node<int>* adj_;
//    void clear(Node<int>* n);
};

// TODO: check class
// TODO: create normal makefile
class DirectedDFS {
public:
    DirectedDFS(DiGraph *g, int s);
    ~DirectedDFS();
    bool marked(int v) { return marked_[v]; }
private:
    bool *marked_;
    void dfs(DiGraph *g, int v);
};


class DirectedCycle {
public:
    DirectedCycle(DiGraph* g);
    ~DirectedCycle();
    bool hasCycle() { return cycle_ != nullptr; }
    Node<int>* cycle() { return cycle_; }
private:
    Node<int>* cycle_;
    bool* marked_;
    bool* onStack_;
    int* edgeTo_;
    void dfs(DiGraph* g, int v);
};


class DepthFirstOrder {
public:
    DepthFirstOrder(DiGraph* d);
    ~DepthFirstOrder();
    std::stack< int >* reservePost() { return reservePost_; }
    std::queue< int >* pre() { return pre_; }
    std::queue< int >* post() { return post_; }
private:
    bool* marked_;
    std::stack< int >* reservePost_;
    std::queue< int >* pre_;
    std::queue< int >* post_;
    void dfs(DiGraph* g, int v);
};


class Topological {
public:
    Topological(DiGraph* d);
    std::stack< int >* order() { return dfo_->reservePost(); }
    bool isDAG() { return dfo_ != nullptr; }
private:
    DepthFirstOrder* dfo_;

};


class KosarajuSCC {
public:
    KosarajuSCC(DiGraph *g);
    ~KosarajuSCC();
    bool stronglyConnected(int v, int w) { return id_[v] == id_[w]; }
    int count() { return count_; }
    int id(int v) { return id_[v]; }
private:
    int count_;
    bool* marked_;
    int* id_;
    void dfs(DiGraph* g, int v);
};


class TransitiveClosure {
public:
    TransitiveClosure(DiGraph *g);
    ~TransitiveClosure();
    bool reachable(int v, int w);
private:
    std::vector<DirectedDFS *> vDFS;
};


int testDiGraph(int argc, char *argv[]);

#endif // DIGRAPH_H
