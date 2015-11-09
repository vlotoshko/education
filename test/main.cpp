#include <iostream>

class Base1 {
public:
  int a;
};

class Base2 {
public:
  char a;
};

class Derived : public Base1, public Base2 {

};

int main(int argc, char const *argv[]) {
  std::cout << "Hello, world!" << std::endl;

  Derived *d = new Derived;
  Base1 *b1 = d;
  Base2 *b2 = d;

  if (d == b1) {
    std::cout << "d == b1" << std::endl;
  }

  if (d == b2) {
    std::cout << "d == b2" << std::endl;
  }

  void *v1 = b1;
  void *v2 = b2;
  void *vd = d;

  std::cout << b1 << std::endl;
  std::cout << b2 << std::endl;
  std::cout << d << std::endl << std::endl;

  std::cout << v1 << std::endl;
  std::cout << v2 << std::endl;
  std::cout << vd << std::endl;

  std::cout << "d == v1: " << std::boolalpha << (d == v1) << std::endl;
  std::cout << "d == v2: " << std::boolalpha << (d == v2) << std::endl;


  return 0;
}
