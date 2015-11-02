#include "cvisitor.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace BehaviourPatterns {
class Visitor;

class Element {
public:
  virtual void accept( Visitor& ) = 0;
};


class This : public Element {
public:
  void accept( Visitor& );
  string thiss() {
    return "This";
  }
};


class That : public Element {
public:
  void accept( Visitor& );
  string that() {
   return "That";
  }
};


class Other : public Element {
public:
  void accept( Visitor& );
  string other() {
    return "Other";
  }
};

class Visitor {
public:
  virtual void visit( This* e ) = 0;
  virtual void visit( That* e ) = 0;
  virtual void visit( Other* e ) = 0;
};

void This::accept( Visitor& v ) {
  v.visit( this );
}

void  That::accept( Visitor& v ) {
  v.visit( this );
}

void  Other::accept( Visitor& v ) {
  v.visit( this );
}



class UpVisitor : public Visitor {
  void visit( This* e ) {
    cout << "Do Up on " + e->thiss() << endl;
  }
  void visit( That* e ) {
    cout << "Do Up on " + e->that() << endl;
  }
  void visit( Other* e ) {
    cout << "Do Up on " + e->other() << endl;
  }
};

class DownVisitor : public Visitor {
  void visit( This* e ) {
    cout << "Do Down on " + e->thiss() << endl;
  }
  void visit( That* e ) {
    cout << "Do Down on " + e->that() << endl;
  }
  void visit( Other* e ) {
    cout << "Do Down on " + e->other() << endl;
  }
};

}

void BehaviourPatterns::cVisitor() {
  Element* elems[] = { new This(), new That(), new Other };

  UpVisitor up;
  DownVisitor down;

  for (int i = 0; i < 3; ++i)
    elems[i]->accept(up);

  for (int i = 0; i < 3; ++i)
    elems[i]->accept(down);
}
