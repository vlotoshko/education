#include "cmemento.h"

#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace BehaviourPatterns {
class Number;

class Memento {
public:
  Memento( int val ) : _state( val ) {}
private:
  friend class Number;
  int _state;
};


class Number {
public:
  Number( int v ) : _value( v ) {}
  void dubble() {
    _value *= 2;
  }
  void half() {
    _value /= 2;
  }
  int getValue() {
    return _value;
  }
  Memento* createMemento() {
    return new Memento( _value );
  }
  void reinstateMemento( Memento* mem ) {
    _value = mem->_state;
  }
private:
  int _value;
};


class CommandM {
public:
  typedef void( Number::* Action)();
  CommandM( Number* n, Action a ) : _receiver( n ), _action( a ) {}
  virtual void execute() {
    _mementoList[_numCommands] = _receiver->createMemento();
    _commandList[_numCommands] = this;
    if( _numCommands > _highWater )
      _highWater = _numCommands;
    ++_numCommands;
    ( _receiver->*_action )();
  }
  static void undo () {
    if ( _numCommands == 0 ) {
      cout << "*** Attempt to run off the end!! ***" << endl;
      return;
    }
    _commandList[ _numCommands - 1 ]->_receiver->reinstateMemento(
      _mementoList[ _numCommands - 1 ] );
    --_numCommands;
  }
  static void redo() {
    if ( _numCommands > _highWater ) {
      cout << "*** Attempt to run off the end!! ***" << endl;
      return;
    }
    ( _commandList[_numCommands]->_receiver->*( _commandList[_numCommands]->_action) )();
    ++_numCommands;
  }
protected:
  Number* _receiver;
  Action _action;
  static CommandM* _commandList[20];
  static Memento* _mementoList[20];
  static int _numCommands;
  static int _highWater;
};


CommandM* CommandM::_commandList[];
Memento* CommandM::_mementoList[];
int CommandM::_numCommands = 0;
int CommandM::_highWater = 0;


}


void BehaviourPatterns::cMemento() {
  int i;
  cout << "Integer: ";
  cin >> i;
  Number* object = new Number( i );

  CommandM* commands[3];
  commands[1] = new CommandM( object, &Number::dubble );
  commands[2] = new CommandM( object, &Number::half );

  cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
  cin >> i;
  while( i ) {

    if( i == 3 ) {
      CommandM::undo();
    }
    else if( i == 4 )
      CommandM::redo();
    else
      commands[i]->execute();
    cout << "  " << object->getValue() <<  endl;
    cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
    cin >> i;
  }
}
