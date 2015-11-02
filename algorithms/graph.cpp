#include <fstream>
#include <stack>
#include <queue>
#include "graph.h"

Graph::Graph(int v) : v_(v), e_(0), adj_(new Node<int>[v]) {
    for (int i = 0; i < v_; ++i) {
        adj_[i].val = i;
    }
}

Graph::Graph(std::string fileName) : e_(0) {
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

Graph::~Graph() {
    delete[] adj_;
}

void Graph::addEdge(int v, int w) {
    adj_[v].add(new Node<int>(w));
    adj_[w].add(new Node<int>(v));
    ++e_;
}

Node<int>* Graph::adj(int v) {
    return &adj_[v];
}

void Graph::toString() {
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


int Graph::degree(Graph *g, int v) {
    int degree = 0;
    Node<int> * n = g->adj(v);
    while(n->next) {
        ++degree;
        n = n->next;
    }
    return degree;
}

int Graph::maxDegree(Graph *g) {
    int max = 0;
    for (int i = 0; i < g->V(); ++i) {
        int d = degree(g, i);
        if (d > max)
            max = d;
    }
    return max;
}

int Graph::avgDegree(Graph *g) {
    return 2 * g->E() / g->V();
}

int Graph::selfLoops(Graph *g) {
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


DeepFirstSearch::DeepFirstSearch(Graph* g, int s) : marked_(new bool[g->V()]) {
    for (int i = 0; i < g->V(); ++i) {
        marked_[i] = false;
    }
    dfs(g ,s);
}


DeepFirstSearch::~DeepFirstSearch() {
    delete[] marked_;
}

void DeepFirstSearch::dfs(Graph *g, int v) {
    marked_[v] = true;
    ++count_;
    Node< int >* n = g->adj(v)->next;
    while(n) {
        if (!marked_[n->val]) {
            std::cout << v << " - " << n->val << std::endl;
            dfs(g, n->val);
        }
        n = n->next;
    }
}


DeepFirstPaths::DeepFirstPaths(Graph* g, int s) : s_(s) {
    marked_ = new bool[g->V()];
    edgeTo_ = new int[g->V()];
    for (int i = 0; i < g->V(); ++i) {
        marked_[i] = false;
    }
    dfs(g ,s);
}

DeepFirstPaths::~DeepFirstPaths() {
    delete[] marked_;
    delete[] edgeTo_;
}

void DeepFirstPaths::dfs(Graph *g, int v) {
    marked_[v] = true;

    Node< int >* n = g->adj(v)->next;
    while(n) {
        if (!marked_[n->val]) {
            std::cout << v << " - " << n->val << std::endl;
            edgeTo_[n->val] = v;
            dfs(g, n->val);
        }
        n = n->next;
    }
}

void DeepFirstPaths::pathTo(int v) {
    if(!hasPathTo(v)) {
        std::cout << "none";
        return;
    }

    std::stack< int > path;

    for (int i = v; i != s_; i = edgeTo_[i]) {
        path.push(i);
    }
    path.push(s_);

    while (!path.empty()) {
       std::cout << path.top();
       path.pop();
       std::cout << (!path.empty() ? " - " : "");
    }
    std::cout << std::endl;
}



BreadthFirstPath::BreadthFirstPath(Graph* g, int s)
  : s_(s), marked_(new bool[g->V()]), edgeTo_(new int[g->V()]) {
    for (int i = 0; i < g->V(); ++i) {
        marked_[i] = false;
    }
    bfs(g ,s);
}

BreadthFirstPath::~BreadthFirstPath() {
    delete[] marked_;
    delete[] edgeTo_;
}

void BreadthFirstPath::bfs(Graph *g, int v) {
    marked_[v] = true;
    std::queue< int > queue; // = new std::queue< int >();
    queue.push(v);

    while (!queue.empty()) {
        int x = queue.front();
        queue.pop();
        Node< int >* n = g->adj(x)->next;

        while(n) {
            if (!marked_[n->val]) {
                std::cout << x << " - " << n->val << std::endl;
                edgeTo_[n->val] = x;
                marked_[n->val] = true;
                queue.push(n->val);
            }
            n = n->next;
        }
    }
}


void BreadthFirstPath::pathTo(int v) {
    if(!hasPathTo(v)) {
        std::cout << "none";
        return;
    }

    std::stack< int > path;

    for (int i = v; i != s_; i = edgeTo_[i]) {
        path.push(i);
    }
    path.push(s_);

    while (!path.empty()) {
       std::cout << path.top();
       path.pop();
       std::cout << (!path.empty() ? " - " : "");
    }
    std::cout << std::endl;
}


CCGraph::CCGraph(Graph* g) : count_(0), marked_(new bool[g->V()]), id_(new int[g->V()]) {
    for (int i = 0; i < g->V(); ++i) {
        marked_[i] = false;
    }

    for (int i = 0; i < g->V(); ++i) {
        if(!marked_[i]) {
            dfs(g, i);
            ++count_;
        }
    }
}

CCGraph::~CCGraph() {
    delete[] marked_;
    delete[] id_;
}


void CCGraph::dfs(Graph *g, int v) {
    marked_[v] = true;
    id_[v] = count_;

    Node< int >* n = g->adj(v)->next;
    while(n) {
        if (!marked_[n->val]) {
            dfs(g, n->val);
        }
        n = n->next;
    }
}

bool CCGraph::connected(int v, int w) {
    return id_[v] == id_[w];
}

int CCGraph::id(int v) {
    return id_[v];
}

int CCGraph::count() {
    return count_;
}


Cycle::Cycle(Graph *g) : hasCycle_(false), marked_(new bool[g->V()]) {
    for (int i = 0; i < g->V(); ++i) {
        marked_[i] = false;
    }

    for (int s = 0; s < g->V(); ++s) {
       if(!marked_[s])
           dfs(g ,s, s);
    }
}


Cycle::~Cycle() {
    delete[] marked_;
}

void Cycle::dfs(Graph *g, int v, int u) {
    marked_[v] = true;

    Node< int >* n = g->adj(v)->next;
    while(n) {
        if (!marked_[n->val]) {
            dfs(g, n->val, v);
        }
        else if (n->val != u) {
            hasCycle_ = true;
        }

        n = n->next;
    }
}

TwoColors::TwoColors(Graph* g)
  : isTwoColors_(true), marked_(new bool[g->V()]), colors_(new bool[g->V()]) {
    for (int i = 0; i < g->V(); ++i) {
        marked_[i] = false;
        colors_[i] = false;
    }

    for (int i = 0; i < g->V(); ++i) {
        if(!marked_[i]) {
            dfs(g, i);
        }
    }
}

TwoColors::~TwoColors() {
    delete[] marked_;
    delete[] colors_;
}


void TwoColors::dfs(Graph *g, int v) {
    marked_[v] = true;

    Node< int >* n = g->adj(v)->next;
    while(n) {
        if (!marked_[n->val]) {
            colors_[n->val] = !colors_[v];
            dfs(g, n->val);
        }
        else if(colors_[n->val] == colors_[v]) {
            std::cout << "color: " << n->val << " - " << v << std::endl;
            isTwoColors_ = false;
        }
        n = n->next;
    }
}


SymbolGraph::SymbolGraph(std::string fileName) : st_(new std::map< std::string, int >) {
    std::ifstream file;
    file.open (fileName);
    std::string line;
    std::string delimiter = " ";


    // Generating map
    while (std::getline(file, line)) {

        size_t pos = 0;
        std::string token;

        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);

            auto it = st_->begin();
            if (st_->find(token) == st_->end()) {
                st_->insert(it, std::pair<std::string, int>(token, st_->size()));
            }
            line.erase(0, pos + delimiter.length());
        }

        auto it = st_->begin();
        if (st_->find(line) == st_->end()) {
            st_->insert(it, std::pair<std::string, int>(line, st_->size()));
        }
    }

    // Generating inverted list
    keys_ = new std::string[st_->size()];
    for (auto i : *st_)
        keys_[i.second] = i.first;

    // Generating graph
    g_ = new Graph(st_->size());

    file.clear();
    file.seekg(0, std::ios::beg);

    while (std::getline(file, line)) {
        size_t pos = 0;
        int v = 0;
        std::string vertex;

        if ((pos = line.find(delimiter)) != std::string::npos) {
            vertex = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
        }

        v = st_->find(vertex)->second;
//        std::cout << "vertex - " << vertex;
//        std::cout << " - " << v << std::endl;

        while ((pos = line.find(delimiter)) != std::string::npos) {
            std::string token = line.substr(0, pos);
//            std::cout << "vertex - " << vertex << "; token = " << token << std::endl;
            g_->addEdge(v, st_->find(token)->second);
            line.erase(0, pos + delimiter.length());
        }

        // add token after last delimiter
        g_->addEdge(v, st_->find(line)->second);
    }

    std::cout << "map: " << std::endl;
    for (auto i : *st_) {
        std::cout << "[" << i.first << "] [" << i.second << "]" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "inverted index: " << std::endl;
    for (size_t var = 0; var < st_->size(); ++var) {
        std::cout << var << " - " << keys_[var] << std::endl;
    }
    std::cout << std::endl;
}

SymbolGraph::~SymbolGraph() {
    delete st_;
    delete[] keys_;
    delete g_;
}

int SymbolGraph::index(std::string key) {
    auto it = st_->find(key);
    if (it == st_->end()) {
        return -1;
    }
    else
        return it->second;
}


int testGraph(int argc, char *argv[]) {

    if (argc > 2) {
        std::string fileName = argv[2];
        Graph gr(fileName);
        gr.toString();

        std::cout << "degree 5: " << Graph::degree(&gr, 5) << std::endl;
        std::cout << "max degree: " << Graph::maxDegree(&gr) << std::endl;
        std::cout << "avg degree: " << Graph::avgDegree(&gr) << std::endl;
        std::cout << "self Loops: " << Graph::selfLoops(&gr) << std::endl;

        DeepFirstSearch dfs(&gr, 0);
        DeepFirstPaths dfp(&gr, 0);

        std::cout << std::endl;
        std::cout << "deep: ";
        dfp.pathTo(5);
        std::cout << std::endl;

        BreadthFirstPath bfp(&gr, 0);
        std::cout << "breadth: ";
        bfp.pathTo(5);
        std::cout << std::endl;

        CCGraph ccg(&gr);
        std::cout << "components: " << ccg.count();
        std::cout << std::endl;

        Cycle cg(&gr);
        std::cout << "has cycle: " << std::boolalpha << cg.hasCycle();
        std::cout << std::endl;

        TwoColors tcg(&gr);
        std::cout << "is bipartite: " << std::boolalpha << tcg.isBipartite();
        std::cout << std::endl;
    }
    return 0;
}


int testSymbolGraph(int argc, char *argv[]) {

    if (argc > 2) {
        std::string fileName = argv[2];
        SymbolGraph gr(fileName);

        std::cout << "graph: " << std::endl;
        gr.G().toString();

        if (argc > 3) {
            BreadthFirstPath bfp(&(gr.G()), gr.index(argv[3]));
            std::string sink;
            while(std::cin >> sink) {
                int i = gr.index(sink);
                if(bfp.hasPathTo(i)) {
                    bfp.pathTo(i);
                }
                else
                    std::cout << "no path :( " << std::endl;
            }
        }

    }
    return 0;
}
