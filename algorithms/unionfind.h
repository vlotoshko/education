#ifndef UNIONFIND_H
#define UNIONFIND_H
#include "tools.h"

template< typename T >
class RandomPair {
public:
    RandomPair(T min, T max) : a_(random(min, max)), b_(random(min, max)){}
    RandomPair() : a_(0), b_(0){}
    void generate(T min, T max) {a_ = random(min, max); b_ = random(min, max);}
    T a() const { return a_; }
    T b() const { return b_; }
private:
    T a_;
    T b_;
};

class TQuickSearch{};
class TQuickUnion{};
class TWeightedQuickUnion{};

class UF {
public:
  UF(int count);
  ~UF();

  int count() const { return count_; }
  int components() const { return components_; }
  int finds() const { return finds_; }
  int unions() const { return unions_; }
  int id(int i) const { finds_++; return id_[i]; }
  bool connected(const int p, const int q) const { return find(p) == find(q); }
  std::ostream& operator <<(std::ostream &out);

  template< class T = TQuickSearch >
  int find(int p) const;
  template< class T = TQuickSearch >
  void union_(const int p, const int q);
private:
    int count_;
    int components_;
    mutable int finds_;
    int unions_;
    int *id_;
    int *sz_;
};


int testUnionFind(int argc, char *argv[]);

#endif // UNIONFIND_H
