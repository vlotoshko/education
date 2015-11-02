#include "cinterpreter.h"
#include <cstring>
#include <map>
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;


namespace BehaviourPatterns {

class Thousand;
class Hundred;
class Ten;
class One;


class RNInterpreter {
public:
  RNInterpreter(); // ctor for client
  RNInterpreter( int ) {} // ctof for subclasses aviods infinite loop
  int interpret( char* ); // interpret for client
  virtual void interpret( char* input, int& total ) {
    // for internal use
    int index = 0;
    if( !strncmp(input, nine(), 2 ) ) {
      total += 9 * multiplier();
      index += 2;
    }
    else if( !strncmp(input, four(), 2 ) ) {
      total += 4 * multiplier();
      index += 2;
    }
    else {
      if( input[0] == five() ) {
        total += 5 * multiplier();
        index += 1;
      }
      else
        index = 0;
      for( int end = index + 9; index < end; ++index )
        if( input[index] == one() )
          total += 1 * multiplier();
        else
          break;
    }
    strcpy( input, &(input[index] ) );
  }
protected:
  // cannot be pure virtual because client asks for instance
   virtual char one() {}
   virtual char* four() {}
   virtual char five() {}
   virtual char* nine() {}
   virtual int multiplier() {}
private:
  RNInterpreter* _thousands;
  RNInterpreter* _hundreds;
  RNInterpreter* _tens;
  RNInterpreter* _ones;
};



class Thousand : public RNInterpreter {
public:
  // provide 1-arg ctor to avoide infinite loop in base class ctor
  Thousand( int ) : RNInterpreter(1) {}
protected:
  char one() {
    return 'M';
  }
  char* four() {
    return "";
  }
  char five() {
    return '\0';
  }
  char* nine() {
    return "";
  }
  int multiplier() {
    return 1000;
  }
};


class Hundred: public RNInterpreter {
public:
  Hundred( int ): RNInterpreter( 1 ) {}
protected:
  char one() {
    return 'C';
  }
  char* four() {
    return "CD";
  }
  char five() {
    return 'D';
  }
  char* nine() {
    return "CM";
  }
  int multiplier() {
    return 100;
  }
};

class Ten: public RNInterpreter {
public:
  Ten( int ): RNInterpreter( 1 ) {}
protected:
  char one() {
    return 'X';
  }
  char* four() {
    return "XL";
  }
  char five() {
    return 'L';
  }
  char* nine() {
    return "XC";
  }
  int multiplier() {
    return 10;
  }
};

class One: public RNInterpreter {
public:
  One( int ): RNInterpreter( 1 ) {}
protected:
  char one() {
    return 'I';
  }
  char* four() {
    return "IV";
  }
  char five() {
    return 'V';
  }
  char* nine() {
    return "IX";
  }
  int multiplier() {
    return 1;
  }
};


RNInterpreter::RNInterpreter() {
  // use 1-arg ctor to avoid infinite loop
  _thousands = new Thousand(1);
  _hundreds = new Hundred(1);
  _tens = new Ten(1);
  _ones = new One(1);
}

int RNInterpreter::interpret(char *input) {
  int total;
  total = 0;
  _thousands->interpret(input, total);
  _hundreds->interpret(input, total);
  _tens->interpret(input, total);
  _ones->interpret(input, total);
  if (strcmp(input, ""))
  // if input was invalid, return 0
    return 0;
  return total;
}

}

namespace BehaviourPatterns {
/*
 * BooleanExp ::= VariableExp | Constant | OrExp | AndExp | NotExp | '(' BooleanExp ')'
 * AndExp ::= BooleanExp 'and' BooleanExp
 * OrExp ::= BooleanExp 'or' BooleanExp
 * NotExp ::= 'not' BooleanExp
 * Constant ::= 'true' | 'false'
 * VariableExp ::= 'A' | 'B' | ... | 'X' | 'Y' | 'Z'
 */


class Context;
class BooleanExp {
public:
  BooleanExp() {}
  virtual ~BooleanExp(){}
  virtual bool evaluate( Context& ) = 0;
};



class VariableExp;
class Context {
public:
//   Context() {
//   }
  bool Lookup ( const char* ) const;
  void Assign ( VariableExp*, bool);
private:
  std::map< const char*, bool > _variables;
};



class VariableExp : public  BooleanExp {
public:
  VariableExp( const char* name ) {
    _name = strdup( name );
  }
  virtual ~VariableExp() {};
  virtual bool evaluate( Context& );
  char* name() const { return _name; }
private:
  char* _name;
};

bool VariableExp::evaluate( Context& a ) {
 return a.Lookup( _name );
}


void Context::Assign( VariableExp* exp, bool b ) {
  _variables[exp->name()] = b;
}

bool Context::Lookup( const char* name ) const {
  return _variables.at(name);
}

class AndExp : public BooleanExp {
public:
  virtual ~AndExp() {
    delete _operand1;
    delete _operand2;
  }
  AndExp( BooleanExp* op1, BooleanExp* op2 ) : _operand1( op1 ), _operand2( op2 ) {}
  bool evaluate( Context& a ) {
    return _operand1->evaluate( a ) && _operand2->evaluate( a );
  }
private:
  BooleanExp* _operand1;
  BooleanExp* _operand2;
};


class OrExp : public BooleanExp {
public:
  virtual ~OrExp() {
    delete _operand1;
    delete _operand2;
  }
  OrExp( BooleanExp* op1, BooleanExp* op2 ) : _operand1( op1 ), _operand2( op2 ) {}
  bool evaluate( Context& a ) {
    return _operand1->evaluate( a ) || _operand2->evaluate( a );
  }
private:
  BooleanExp* _operand1;
  BooleanExp* _operand2;
};


class NotExp : public BooleanExp {
public:
  virtual ~NotExp() {
    delete _operand;
  }
  NotExp( BooleanExp* op ) : _operand( op ) {}
  bool evaluate( Context& a ) {
    return !( _operand->evaluate( a ) );
  }
private:
  BooleanExp* _operand;
};


class Constant : public BooleanExp {
public:
  Constant( bool v ) : _value( v ) {}
  bool evaluate( Context& a ) {
    return _value;
  }
private:
  bool _value;
};

}

void BehaviourPatterns::cInterpreterRome() {
  RNInterpreter interpreter;
  char input[20];
  cout << "Enter Roman Numeral: ";
  while ( cin >> input ) {
    cout << "   interpretation is "
         << interpreter.interpret(input) << endl;
    cout << "Enter Roman Numeral: ";
  }
}


void BehaviourPatterns::cInterpreterBoolean() {
  // (true and x ) or ( y and not( x ) )

  BooleanExp* expression;


  VariableExp* x = new VariableExp( "X" );
  VariableExp* y = new VariableExp( "Y" );

  expression = new OrExp(
    new AndExp( new Constant( true ), x ),
    new AndExp( y, new NotExp( x ))
  );

  Context context1;
  context1.Assign( x, false );
  context1.Assign( y, true );

  Context context2;
  context2.Assign( x, true );
  context2.Assign( y, false );

  Context context3;
  context3.Assign( x, true );
  context3.Assign( y, true );

  Context context4;
  context4.Assign( x, false );
  context4.Assign( y, false );

  cout << std::boolalpha << expression->evaluate( context1 ) << endl;
  cout << std::boolalpha << expression->evaluate( context2 ) << endl;
  cout << std::boolalpha << expression->evaluate( context3 ) << endl;
  cout << std::boolalpha << expression->evaluate( context4 ) << endl;

//   delete x;
//   delete y;
  delete expression;
}
