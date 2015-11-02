#include "ctemplatemethod.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace BehaviourPatterns {

class Base {
public:
  void execute() {
    a();
    ph1();
    c();
    ph2();
    e();
  }
private:
  void a() {
    cout << "a ";
  }
  void c() {
    cout << "c ";
  }
  void e() {
    cout << "e ";
  }
  virtual void ph1() = 0;
  virtual void ph2() = 0;
};


class One : public Base {
public:
  void ph1() {
    cout << "b ";
  }
  void ph2() {
    cout << "d ";
  }
};


class Two : public Base {
public:
  void ph1() {
    cout << "2 ";
  }
  void ph2() {
    cout << "4 ";
  }
};

}

void BehaviourPatterns::cTemplateMethod() {
  Base* array[] = { new One, new Two };
  for (size_t i = 0; i < 2; ++i) {
    array[i]->execute();
  }
}
