#include "citeration.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace BehaviourPatterns {
class StackIter;
class Stack {
public:
  friend class StackIter;
  Stack() : _sp( -1 ) {}

  void push( int i ) {
    _items[++_sp] = i;
  }

  int pop() {
    return _items[_sp--];
  }

  bool isEmpty() {
    return _sp == -1;
  }

  StackIter* createIterator() const;
private:
  int _items[10];
  int _sp;
};


class StackIter {
public:
  StackIter( const Stack* s ) : _stk( s ) {}
  void first() {
    _index = 0;
  }

  void next() {
    _index++;
  }

  bool isDone() {
    return _index == _stk->_sp + 1;
  }

  int currentItem() {
    return _stk->_items[_index];
  }
private:
  const Stack* _stk;
  int _index;
};


StackIter* Stack::createIterator() const {
  return new StackIter( this );
}


bool operator== ( const Stack& lhs, const Stack& rhs ) {
  StackIter* itl = lhs.createIterator();
  StackIter* itr = rhs.createIterator();

  for( itl->next(), itr->next(); !itl->isDone(); itl->next(), itr->next() )
    if( itl->currentItem() != itr->currentItem() )
      break;
  bool result = itl->isDone() && itr->isDone();
  delete itl;
  delete itr;
  return result;
}


}


void BehaviourPatterns::cIteration() {
  Stack s1;
  for( int i = 0; i < 5; ++i )
    s1.push(i);

  Stack s2( s1 );
  Stack s3( s1 );
  Stack s4( s1 );
  Stack s5( s1 );

  s3.pop();
  s5.pop();
  s4.push( 2 );
  s5.push( 9 );

  cout << "1 == 2 is " << (s1 == s2) << endl;
  cout << "1 == 3 is " << (s1 == s3) << endl;
  cout << "1 == 4 is " << (s1 == s4) << endl;
  cout << "1 == 5 is " << (s1 == s5) << endl;

  StackIter* iter = s5.createIterator();
  iter->first();

  while( !iter->isDone() ) {
    cout << iter->currentItem() << endl;
    iter->next();
  }
}
