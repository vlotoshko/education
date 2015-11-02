#include "bproxy.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace StructuralPatterns {
class RealImage {
public:
  RealImage( int i ) : _id( i ) {
    cout << "  $$ ctor " << _id << endl;
  }
  ~RealImage() {
    cout << "  dtor " << _id << endl;
  }
  void draw() {
    cout << "  drawing image " << _id << endl;
  }
private:
  int _id;
};


class Image {
public:
  Image() {
    _id = _next++;
    _real = 0;
  }
  ~Image() {
    delete _real;
  }
  void draw() {
    if( !_real )
      _real = new RealImage( _id );
    _real->draw();
  }
private:
  RealImage* _real;
  int _id;
  static int _next;
};

int Image::_next = 1;

}

// lazy initialization
void StructuralPatterns::bProxy() {
  Image image[5];

  int i = 0;
  while( true ) {
    cout << "Image [1-5]: ";
    cin >> i;
    if( i == 0 )
      break;
    image[i - 1].draw();
  }
}
