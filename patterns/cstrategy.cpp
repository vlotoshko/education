#include "cstrategy.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace BehaviourPatterns {
class Compression {
public:
  virtual ~Compression() {}
  virtual void compress( const string& ) = 0;
};


class ZIP_Compression : public Compression {
public:
  void compress( const string& file ) {
    cout << "ZIP compression: " << file << endl;
  }
};


class ARJ_Compression : public Compression {
public:
  void compress( const string& file ) {
    cout << "ARJ compression: " << file << endl;
  }
};


class RAR_Compression : public Compression {
public:
  void compress( const string& file ) {
    cout << "RAR compression: " << file << endl;
  }
};

// TODO write comment here
class Compressor {
public:
  Compressor( Compression* c ) : _compr( c ) {}
  ~Compressor() { delete _compr; }
  void compress ( const string& file ) {
    _compr->compress( file );
  }
private:
  Compression* _compr;
};

}

void BehaviourPatterns::cStrategy() {
  Compressor* c = new Compressor( new ZIP_Compression() );
  c->compress("file.txt");

  delete c;
}
