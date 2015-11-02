#include "asingleton.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace CreationalPatterns {

class SimpleSingleton {
private:
  SimpleSingleton() {}
  SimpleSingleton( const SimpleSingleton& );
  SimpleSingleton operator=( const SimpleSingleton& );
public:
  static SimpleSingleton& getInstance() {
    static SimpleSingleton instance;
    return instance;
  }
};

}

void CreationalPatterns::aSingleton() {
  cout << "see simple Meyers singleton in description" << endl;
}
