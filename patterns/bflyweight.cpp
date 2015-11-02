#include "bflyweight.h"
#include <iostream>
#include <cstring>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace StructuralPatterns {
class Icon {
public:
  Icon( char* fileName ) {
    strcpy( _name, fileName );
    if( !strcmp( fileName, "go" ) ) {
      _width = 20;
      _height = 20;
    }
    if( !strcmp( fileName, "stop" ) ) {
      _width = 40;
      _height = 40;
    }
    if( !strcmp( fileName, "select" ) ) {
      _width = 60;
      _height = 60;
    }
     if( !strcmp( fileName, "undo" ) ) {
      _width = 30;
      _height = 30;
    }
  }
  const char* getName() {
    return _name;
  }
  void draw( int x, int y ) {
    cout << "\tdrawing " << _name
         << ": upper left (" << x << "," << y
         << ") lower right (" << x + _width << "," << y + _height
         << ")" << endl;
  }
private:
  char _name[20];
  int _width;
  int _height;
};

class FlyweightFactory {
public:
  static Icon* getIcon( char* name ) {
    for( int i = 0; i < _numIcons; ++i )
      if( !strcmp( name, _icons[i]->getName() ) )
        return _icons[i];
      _icons[_numIcons] = new Icon( name );
      cout << "created new icon: " << name << endl;
      return _icons[_numIcons++];
  }
  static void repotTheIcons() {
    cout << "Active Flyweights: ";
    for( int i = 0; i < _numIcons; ++i ) {
      cout << _icons[i]->getName();
      cout << endl;
    }
  }
private:
  enum { MAX_ICONS = 5 };
  static int _numIcons;
  static Icon* _icons[MAX_ICONS];
};

int FlyweightFactory::_numIcons = 0;
Icon* FlyweightFactory::_icons[];


class DialogBox {
public:
  DialogBox( int x, int y, int incr ) : _iconOriginX( x ), _iconOriginY( y ),
    _iconXincrement( incr ) {}
  virtual void draw() = 0;
  virtual ~DialogBox() {}
protected:
  Icon* _icons[3];
  int _iconOriginX;
  int _iconOriginY;
  int _iconXincrement;
};


class FileSelection : public DialogBox {
public:
  FileSelection( Icon* first, Icon* second, Icon* third ) : DialogBox( 100, 100, 100 ) {
    _icons[0] = first;
    _icons[1] = second;
    _icons[2] = third;
  }
  void draw() {
    cout << "drawing file selection icons:" << endl;
    for( int i = 0; i < 3; ++i )
      _icons[i]->draw( _iconOriginX + ( i * _iconXincrement ), _iconOriginY );
  }
};

class CommintTransaction : public DialogBox {
public:
  CommintTransaction( Icon* first, Icon* second, Icon* third ) : DialogBox( 150, 150, 150  ) {
    _icons[0] = first;
    _icons[1] = second;
    _icons[2] = third;
  }
  void draw() {
    cout << "drawing commit transaction icons:" << endl;
    for( int i = 0; i < 3; ++i )
      _icons[i]->draw( _iconOriginX + ( i * _iconXincrement ), _iconOriginY );
  }
};


}

void StructuralPatterns::bFlyweight() {
  DialogBox* dialogBox[2];
  dialogBox[0] = new FileSelection(
    FlyweightFactory::getIcon( "go" ),
    FlyweightFactory::getIcon( "stop" ),
    FlyweightFactory::getIcon( "select" ) );

  dialogBox[1] = new CommintTransaction(
    FlyweightFactory::getIcon( "select" ),
    FlyweightFactory::getIcon( "stop" ),
    FlyweightFactory::getIcon( "undo" )
  );

  for( int i = 0; i < 2; ++i )
    dialogBox[i]->draw();

  cout << endl;

  FlyweightFactory::repotTheIcons();
}
