#include "bcomposite.h"
#include <iostream>
#include <vector>
#include <assert.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace StructuralPatterns {


// Component
class Unit {
public:
  virtual int getStrength() = 0;
  virtual void addUnit ( Unit* p ) {
    assert( false );
  }
  virtual ~Unit() {}
};

// Primitive
class Archer : public Unit {
public:
  int getStrength() {
    return 1;
  }
};

// Primitive
class Infantryman : public Unit {
public:
  int getStrength() {
    return 2;
  }
};

// Primitive
class Horseman : public Unit {
public:
  int getStrength() {
    return 3;
  }
};

// Composite
class CompositeUnit : public Unit {
public:
  int getStrength() {
    int total = 0;
    for( size_t i = 0; i < c.size(); ++i )
      total += c[i]->getStrength();
    return total;
  }
  void addUnit( Unit* p ) {
    c.push_back( p );
  }
  ~CompositeUnit() {
    for( size_t i = 0; i < c.size(); ++i )
      delete c[i];
  }
private:
  std::vector< Unit* > c;
};


CompositeUnit* createLegion() {
  CompositeUnit* legion = new CompositeUnit;

  for( int i = 0; i < 3000; ++i )
    legion->addUnit( new Infantryman );

  for( int i = 0; i < 1200; ++i )
    legion->addUnit( new Archer );

  for( int i = 0; i < 300; ++i )
    legion->addUnit( new Horseman );

  return legion;
}

}

void StructuralPatterns::bComposite() {
  CompositeUnit* army = new CompositeUnit;

  for(int i = 0; i < 5; ++i )
    army->addUnit( createLegion() );

  cout << "Army damaging is: " << army->getStrength() << endl;
}
