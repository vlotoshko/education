#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <memory>


class Base1 {
public:
  int a;
  int b;
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
  std::cout << "d == static_cast<Base2 *>(v2): " << std::boolalpha <<
    (d == static_cast<Base2 *>(v2)) << std::endl;

  Base1 b;
  std::cout << "typeid: " << typeid(d).name() << std::endl;
  std::cout << "typeid: " << typeid(b).name() << std::endl;
  std::cout << "typeid: " << typeid(b1).name() << std::endl;
  std::cout << "typeid: " << typeid(*b2).name() << std::endl;

  int f;
  std::cout << "typeid: " << typeid(f).name() << std::endl;
  std::cout << "typeid: " << typeid(0).name() << std::endl;

  std::allocator<int> a1;
  // std::allocator_traits<std::allocator<int>>::allocator_type;
  std::allocator_traits<std::allocator<int>>::allocator_type a2;
  std::allocator_traits<std::allocator<int>>::value_type k;
  std::allocator_traits<decltype(a1)>::value_type k1;
  std::cout << "typeid: " << typeid(std::allocator_traits<std::allocator<int>>::allocator_type).name() << std::endl;
  std::cout << "typeid: " << typeid(k1).name() << std::endl;

  return 0;
}
