#include "ccommand.h"
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace BehaviourPatterns {

class Game {
public:
  void create() {
    cout << "Create game " << endl;
  }

  void open( string file ) {
    cout << "Open game from " << file << endl;
  }

  void save( string file ) {
    cout << "Save game to " << file << endl;
  }

  void make_move( string move ) {
    cout << "Make move " << move << endl;
  }

};


string getPlayerInput( string promt ) {
  string input;
  cout << promt;
  cin >> input;
  return input;
}

class Command {
public:
  virtual ~Command() {}
  virtual void execute() = 0;
protected:
  Command( Game* game ) : _game( game ) {}
  Game* _game;
};


class CreateGameCommand : public Command {
public:
  CreateGameCommand( Game* game ) : Command( game ) {}
  void execute() {
    _game->create();
  }
};

class OpenGameCommand : public Command {
public:
  OpenGameCommand( Game* game ) : Command( game ) {}
  void execute() {
    string fileName;
    fileName = getPlayerInput("Enter file name: ");
    _game->open( fileName );
  }
};


class SaveGameCommand : public Command {
public:
  SaveGameCommand( Game* game ) : Command( game ) {}
  void execute() {
    string fileName;
    fileName = getPlayerInput("Enter file name: ");
    _game->save( fileName );
  }
};


class MakeMoveCommand: public Command
{
  public:
    MakeMoveCommand( Game * p ) : Command( p ) {}
    void execute() {
      // Сохраним игру для возможного последующего отката
      _game->save( "TEMP_FILE" );
      string move;
      move = getPlayerInput( "Enter your move:" );
      _game->make_move( move );
    }
};

class UndoCommand: public Command
{
  public:
    UndoCommand( Game * p ) : Command( p) {}
    void execute() {
      // Восстановим игру из временного файла
      _game->open( "TEMP_FILE");
    }
};

}

void BehaviourPatterns::cCommand() {
  Game game;
  std::vector< Command* > v;
  v.push_back( new CreateGameCommand( &game) );
  v.push_back( new MakeMoveCommand( &game ) );
  v.push_back( new MakeMoveCommand( &game ) );
  v.push_back( new UndoCommand( &game ) );
  v.push_back( new SaveGameCommand ( &game ) );

  for( size_t i = 0; i < v.size(); ++i )
    v[i]->execute();

  for( size_t i = 0; i < v.size(); ++i )
    delete v[i];
}
