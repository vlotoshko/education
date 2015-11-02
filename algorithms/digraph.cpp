#include <fstream>
#include "digraph.h"


DiGraph::DiGraph(int v) : v_(v), e_(0), adj_(new Node<int>[v]) {
    for (int i = 0; i < v_; ++i) {
        adj_[i].val = i;
    }
}

DiGraph::DiGraph(std::string fileName) : e_(0) {
    std::ifstream file;
    file.open (fileName);
    file >> v_;

    adj_ = new Node<int>[v_];
    for (int i = 0; i < v_; ++i) {
        adj_[i].val = i;
    }

    int v;
    int w;
    while (file >> v && file >> w) {
        addEdge(v, w);
    }
}

DiGraph::~DiGraph() {
    delete[] adj_;
}


void DiGraph::addEdge(int v, int w) {
    adj_[v].add(new Node<int>(w));
    ++e_;
}

Node<int>* DiGraph::adj(int v) {
    return &adj_[v];
}


void DiGraph::toString() {
    std::string s;

    std::cout << "vertex: " << v_ << "; edges: " << e_ << std::endl;
    for (int var = 0; var < V(); ++var) {
        std::cout << adj(var)->val << ": ";
        Node<int>* n = adj(var)->next;
        while (n) {
            std::cout << n->val << " ";
            n = n->next;
        }
        std::cout << std::endl;
    }
}

int DiGraph::degree(DiGraph *g, int v) {
    int degree = 0;
    Node<int> * n = g->adj(v);
    while(n->next) {
        ++degree;
        n = n->next;
    }
    return degree;
}

int DiGraph::maxDegree(DiGraph *g) {
    int max = 0;
    for (int i = 0; i < g->V(); ++i) {
        int d = degree(g, i);
        if (d > max)
            max = d;
    }
    return max;
}

int DiGraph::avgDegree(DiGraph *g) {
    return 2 * g->E() / g->V();
}

int DiGraph::selfLoops(DiGraph *g) {
    int count = 0;
    for (int v = 0; v < g->V(); ++v) {
        Node<int>* n = g->adj(v)->next;
        while(n) {
            if (n->val == v)
                ++count;
            n = n->next;
        }
    }
    return count / 2;
}

DiGraph* DiGraph::reverse(DiGraph *g) {
    DiGraph* d = new DiGraph(g->V());
    for (int var = 0; var < g->V(); ++var) {

        int v = g->adj(var)->val;
        Node<int>* n = g->adj(v)->next;
        while(n) {
            d->addEdge(n->val, v);
            n = n->next;
        }
    }
    return d;
}

DirectedDFS::DirectedDFS(DiGraph *g, int s) : marked_(new bool[g->V()]) {
    for (int i = 0; i < g->V(); ++i) {
        marked_[i] = false;
    }
    dfs(g, s);
}

DirectedDFS::~DirectedDFS() {
    delete[] marked_;
}

void DirectedDFS::dfs(DiGraph *g, int v) {
    marked_[v] = true;
    Node< int >* n = g->adj(v)->next;
    while(n) {
        if (!marked_[n->val]) {
            dfs(g, n->val);
        }
        n = n->next;
    }
}

DirectedCycle::DirectedCycle(DiGraph* g)
  : cycle_(nullptr), marked_(new bool[g->V()]),
    onStack_(new bool[g->V()]), edgeTo_(new int[g->V()])  {

    for (int i = 0; i < g->V(); ++i) {
        marked_[i] = false;
        onStack_[i] = false;
    }

    for (int i = 0; i < g->V(); ++i) {
        if(!marked_[i]) {
            dfs(g, i);
        }
    }
}

DirectedCycle::~DirectedCycle() {
    delete[] marked_;
    delete[] onStack_;
    if (cycle_ != nullptr)
        delete cycle_;
}

void DirectedCycle::dfs(DiGraph *g, int v) {
    marked_[v] = true;
    onStack_[v] = true;

//    std::cout << "v: " << v << std::endl;
    Node< int >* n = g->adj(v)->next;
    while(n) {
        if (hasCycle()) return;

//        std::cout << "n->val: " << n->val << std::endl;
        if (!marked_[n->val]) {
            edgeTo_[n->val] = v;
            dfs(g, n->val);
        }
        else
            if(onStack_[n->val]) {
                cycle_ = new Node<int>(n->val);
                for(int x = v; x != n->val; x = edgeTo_[x]) {
                    cycle_ = (new Node<int>(x))->add(cycle_);
                }
                cycle_ = (new Node<int>(n->val))->add(cycle_);
            }
        n = n->next;
    }
    onStack_[v] = false;
}

DepthFirstOrder::DepthFirstOrder(DiGraph* g)
  : marked_(new bool[g->V()]), reservePost_(new std::stack< int >()),
    pre_(new std::queue< int >()), post_(new std::queue< int >()) {

    marked_ = new bool[g->V()];
    reservePost_ =  new std::stack< int >();
    pre_ = new std::queue< int >();
    post_ = new std::queue< int >();
    for (int v = 0; v < g->V(); ++v) {
        if (!marked_[v])
            dfs(g, v);
    }
}


DepthFirstOrder::~DepthFirstOrder() {
    delete reservePost_;
    delete pre_;
    delete post_;
    delete[] marked_;
}


void DepthFirstOrder::dfs(DiGraph* g, int v) {
    marked_[v] = true;

    pre_->push(v);
    Node< int >* n = g->adj(v)->next;
    while(n) {
        if (!marked_[n->val]) {
            dfs(g, n->val);
        }
        n = n->next;
    }
    post_->push(v);
    reservePost_->push(v);
}

Topological::Topological(DiGraph* d) : dfo_( nullptr ) {
    DirectedCycle cycleFinder = DirectedCycle( d );
    if(!cycleFinder.hasCycle()) {
        dfo_ = new DepthFirstOrder( d );
    }
}


KosarajuSCC::KosarajuSCC(DiGraph* g) : count_(0), marked_(new bool[g->V()]), id_(new int[g->V()]) {
    for (int i = 0; i < g->V(); ++i) {
        marked_[i] = false;
    }

    DiGraph* r = DiGraph::reverse(g);

    DepthFirstOrder order(r);

    while(order.reservePost()->size() > 0) {
        int i = order.reservePost()->top();
        if(!marked_[i]) {
            dfs(g, i);
            ++count_;
//            std::cout << std::endl << std::endl;
        }
        order.reservePost()->pop();
    }

    delete r;
}

KosarajuSCC::~KosarajuSCC() {
    delete[] marked_;
    delete[] id_;
}

void KosarajuSCC::dfs(DiGraph *g, int v) {
    marked_[v] = true;
    id_[v] = count_;

//    std::cout << v << std::endl;
    Node< int >* n = g->adj(v)->next;
    while(n) {
        if (!marked_[n->val]) {
            dfs(g, n->val);
        }
        n = n->next;
    }
}

TransitiveClosure::TransitiveClosure(DiGraph *g) {
    for (int v = 0; v < g->V(); ++v) {
        vDFS.push_back(new DirectedDFS(g, v));
    }
}

TransitiveClosure::~TransitiveClosure() {
    for (auto it = vDFS.begin();  it != vDFS.end(); ++it) {
        delete *it;
    }
}

bool TransitiveClosure::reachable(int v, int w) {
    return vDFS[v]->marked(w);
}


int testDiGraph(int argc, char *argv[]) {

    if (argc > 2) {
        std::string fileName = argv[2];
        DiGraph gr(fileName);

        std::cout << "graph: " << std::endl;
        gr.toString();

        std::cout << "dfs: " << std::endl;
        DirectedDFS ddfs(&gr, 0);

        DirectedCycle dc(&gr);

        if (dc.hasCycle()) {
            std::cout << "cycle: " << dc.cycle()->val << " ";
            Node<int>* n = dc.cycle()->next;
            while (n && n != dc.cycle()) {
                std::cout << n->val << " ";
                n = n->next;
            }
            std::cout << std::endl;
        }

        DepthFirstOrder dfo(&gr);

        std::cout << "preorder: " << std::endl;
        while(dfo.pre()->size() > 0) {
            std::cout << dfo.pre()->front() << " ";
            dfo.pre()->pop();
        }
        std::cout << std::endl;

        std::cout << "postorder: " << std::endl;
        while(dfo.post()->size() > 0) {
            std::cout << dfo.post()->front() << " ";
            dfo.post()->pop();
        }
        std::cout << std::endl;


        std::cout << "reserver postorder: " << std::endl;
        while(dfo.reservePost()->size() > 0) {
            std::cout << dfo.reservePost()->top() << " ";
            dfo.reservePost()->pop();
        }
        std::cout << std::endl;

        Topological tpl(&gr);
        std::cout << "topological: " << std::endl;
        if (!tpl.isDAG())
            std::cout << "graph not DAG";
        else
            while(tpl.isDAG() && tpl.order()->size() > 0) {
                std::cout << tpl.order()->top() << " ";
                tpl.order()->pop();
            }
        std::cout << std::endl;

        KosarajuSCC KSCC(&gr);
        std::cout << "KSCC components: " << KSCC.count();
        std::cout << std::endl;

        std::cout << "TransitiveClosure: " << std::endl;
        TransitiveClosure TC(&gr);
        std::cout << "0, 7 reachable: " << std::boolalpha << TC.reachable(0, 7) << std::endl;
        std::cout << "4, 6 reachable: " << std::boolalpha << TC.reachable(4, 6) << std::endl;
        std::cout << "3, 9 reachable: " << std::boolalpha << TC.reachable(3, 9) << std::endl;
        std::cout << "9, 3 reachable: " << std::boolalpha << TC.reachable(9, 3) << std::endl;

    }
    return 0;
}
