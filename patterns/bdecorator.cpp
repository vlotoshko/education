#include "bdecorator.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace StructuralPatterns {
// LCD-class
class Widget {
public:
  virtual void draw() = 0;
  virtual ~Widget() {}
};


class TextWindow : public Widget {
public:
  TextWindow( int h, int w ) : _height( h ), _width( w ) {}
  void draw() {
    cout << "drawing text window with size: " << _height << " x " << _width << endl;
  }
private:
  int _height;
  int _width;
};

// Base decorator
class Decorator : public Widget {
public:
  Decorator( Widget* w) : _inner( w ) {}
  void draw() {
    _inner->draw();
  }
  virtual ~Decorator() {
    delete _inner;
  }
private:
  Widget* _inner;
};


class BorderDecorator : public Decorator {
public:
  BorderDecorator( Widget* w ) : Decorator( w ) {}
  void draw() {
    Decorator::draw();
    cout << "borders drawing" << endl;
  }
};


class ScrollbarDecorator : public Decorator {
public:
  ScrollbarDecorator( Widget* w ) : Decorator( w ) {}
  void draw() {
    Decorator::draw();
    cout << "scrollbar drawing" << endl;
  }
};

}

void StructuralPatterns::bDecorator() {
  Widget* t =
    new BorderDecorator(
      new BorderDecorator(
        new BorderDecorator(
          new BorderDecorator(
            new ScrollbarDecorator(
              new TextWindow( 45, 90 ) ) ) ) ) );
  t->draw();
  delete t;
}
