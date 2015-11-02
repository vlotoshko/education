#include "cchainofresponsibility.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace BehaviourPatterns {
class BaseChain {
public:
  BaseChain() {
    _next = 0;
  }
  void setNext( BaseChain* chain ) {
    _next = chain;
  }
  void addChain( BaseChain* chain ) {
    if( _next != 0 )
      _next->addChain( chain );
    else
      setNext( chain );
  }
  virtual void handle( int i ) {
//     if( !_next != 0 )
      _next->handle( i );
  }
private:
  BaseChain* _next;
};



class Handler1 : public BaseChain {
public:
  void handle( int i ) {
    if( rand() % 3 ) {
      cout << "H1 passed " << i << " ";
      BaseChain::handle( i );
    }
    else
      cout << "H1 handled " << i << " ";
  }
};

class Handler2 : public BaseChain {
public:
  void handle( int i ) {
    if( rand() % 3 ) {
      cout << "H2 passed " << i << " ";
      BaseChain::handle( i );
    }
    else
      cout << "H2 handled " << i << " ";
  }
};

class Handler3 : public BaseChain {
public:
  void handle( int i ) {
    if( rand() % 3 ) {
      cout << "H3 passed " << i << " ";
      BaseChain::handle( i );
    }
    else
      cout << "H3 handled " << i << " ";
  }
};

}


namespace BehaviourPatterns {
class Component {
public:
  Component( int v, Component* c ) : _value( v ), _next( c ) {
  }
  void setNext( Component* n ) {
    _next = n;
  }
  virtual void traverse() {
    cout << _value << " ";
  }
  virtual void volunteer() {
    _next->volunteer();
  }
private:
  int _value;
  Component* _next;
};

class Primitive : public Component {
public:
  Primitive( int v, Component* c = 0 ) : Component( v, c ) {}

  void volunteer() {
    Component::traverse();

    // Primitive object does not handle 5 of 6 requests
    if(  rand() * 100  % 6 != 0 )
      Component::volunteer();
  }
};


class Composite : public Component {
public:
  Composite( int v, Component* c = 0 ) : Component( v, c ) {}

  void add( Component* c ) {
    children.push_back( c );
  }

  void traverse() {
    Component::traverse();
    for( size_t i = 0; i < children.size(); ++i )
      children[i]->traverse();
  }

  void volunteer() {
    Component::volunteer();
  }
private:
  std::vector< Component* > children;
};


}

void BehaviourPatterns::cChainOfResponsibility() {
  srand( time( 0 ) );
  Handler1 root;
  Handler2 two;
  Handler3 thr;

  root.addChain( &two );
  root.addChain( &thr );
  thr.setNext( &root );

  for( int i = 0; i < 10; ++i ) {
    root.handle( i );
    cout << endl;
  }
}

void BehaviourPatterns::cChainOfResponsibilityAndComposite() {
  srand(time(0));                 // 1
  Primitive seven(7);             // |
  Primitive six(6, &seven);       // +-- 2
  Composite three(3, &six);       // |   |
  three.add(&six);
  three.add(&seven);              // |   +-- 4 5
  Primitive five(5, &three);      // |
  Primitive four(4, &five);       // +-- 3
  Composite two(2, &four);        // |   |
  two.add(&four);
  two.add(&five);                 // |   +-- 6 7
  Composite one(1, &two);         // |
  Primitive nine(9, &one);        // +-- 8 9
  Primitive eight(8, &nine);
  one.add(&two);
  one.add(&three);
  one.add(&eight);
  one.add(&nine);
  seven.setNext(&eight);
  cout << "traverse: ";
  one.traverse();
  cout << '\n';
  for (int i = 0; i < 8; i++) {
    one.volunteer();
    cout << '\n';
  }
}
