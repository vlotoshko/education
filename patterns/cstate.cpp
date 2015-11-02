#include "cstate.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace BehaviourPatterns {
class Machine;

class State
{
public:
  ~State() {}
  virtual void on( Machine* ) {
    cout << "  already ON" << endl;
  }

  virtual void off( Machine* ) {
    cout << "  already OFF" << endl;
  }
};


class Machine
{
public:
  Machine();
  void setCurrent( State * s ) {
    _current = s;
  }
  void on() {
    _current->on( this );
  }
  void off() {
    _current->off( this );
  }
private:
  State* _current;
};

class ON : public State
{
public:
  ON() {
    cout << " ON-ctor" << endl;
  }
  ~ON() {
    cout << " ~ON-dtor" << endl;
  }
  void off( Machine* );
};


class OFF : public State
{
public:
  OFF() {
    cout << " OFF-ctor" << endl;
  }
  ~OFF() {
    cout << " ~OFF-dtor" << endl;
  }
  void on( Machine* m ) {
    cout << "   going from OFF to ON" << endl;
    m->setCurrent( new ON() );
    delete this;
  }
};

void ON::off( Machine* m ) {
    cout << "   going from ON to OFF" << endl;
    m->setCurrent( new OFF() );
    delete this;
}

Machine::Machine()
{
  _current = new OFF();
}


}

void BehaviourPatterns::cState() {
  void( Machine:: *ptrs[] )() = { &Machine::off, &Machine::on };
  Machine m;
  int num;
  cout << endl;
  while( true ) {
    cout << "Enter 0/1:";
    cin >> num;
    ( m.*ptrs[num] )();
  }
}
