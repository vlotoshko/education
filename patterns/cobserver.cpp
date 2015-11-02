#include "cobserver.h"
#include <vector>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace BehaviourPatterns {
class Subject;
class Observer {
public:
  Observer( Subject* s ) : _model( s ) {}
  virtual ~Observer() {}
  virtual void update() = 0;
protected:
  Subject* getSubject() {
    return _model;
  }
private:
  Subject* _model;
};

class Subject {
public:
  void attach( Observer* obs) {
    _views.push_back( obs );
  }
  void SetValue( int value ) {
    _value = value;
    notify();
  }
  int getValue() {
    return _value;
  }
  void notify() {
    for( size_t i = 0; i < _views.size(); ++i )
      _views[i]->update();
  }
private:
  std::vector < Observer* > _views;
  int _value;
};


class DivObserver : public Observer {
public:
  DivObserver( Subject* s, int v ) : Observer( s ), _value( v ) {
    s->attach( this );
  }
  void update() {
    int v = getSubject()->getValue();
    cout << _value << " div " << v << " is " <<  _value / v  << endl;
  }
private:
  int _value;
};


class MultObserver : public Observer {
public:
  MultObserver( Subject* s, int v ) : Observer( s ), _value( v ) {
    s->attach( this );
  }
  void update() {
    int v = getSubject()->getValue();
    cout << v << " mult " << _value << " is " <<  v * _value << endl;
  }
private:
  int _value;
};

}

void BehaviourPatterns::cObserver() {
  Subject subj;
  DivObserver div1( &subj, 60 );
  MultObserver mult1( &subj, 3 );
  DivObserver div2( &subj, 42 );
  MultObserver mult2( &subj, 5 );
  subj.SetValue( 3 );
  subj.SetValue( 5 );
}
