#include "afactorymethod.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace CreationalPatterns {

class Product {
public:
  virtual string getName() = 0;
  virtual ~Product(){}
};

class Creator {
public:
  virtual Product* DoMakeProduct() = 0;
  virtual ~Creator(){}
};


class ConcreteProductA : public Product {
public:
  string getName() { return "ConcreteProductA"; }
};

class ConcreteProductB : public Product {
public:
  string getName() { return "ConcreteProductB"; }
};


class ConcreteCreatorA : public Creator {
public:
  Product* DoMakeProduct() { return new ConcreteProductA(); }
};


class ConcreteCreatorB : public Creator {
public:
  Product* DoMakeProduct() { return new ConcreteProductB(); }
};


template< typename T >
class StandartCreator : public Creator {
public:
  Product* DoMakeProduct() { return new T(); }
};

}

void CreationalPatterns::aFactoryMethod() {
  const size_t count = 2;
  ConcreteCreatorA creatorA;
  ConcreteCreatorB creatorB;

  Creator* creators[count] = { &creatorA, &creatorB };

  for( size_t i = 0; i < count; ++i ) {
    Product* prod =  creators[i]->DoMakeProduct();
    cout << prod->getName() << endl;
    delete prod;
  }
}


void CreationalPatterns::aFactoryMethodTemplate() {
  const size_t count = 2;
  StandartCreator< ConcreteProductA > creatorA;
  StandartCreator< ConcreteProductB > creatorB;

  Creator* creators[count] = { &creatorA, &creatorB };

  for( size_t i = 0; i < count; ++i ) {
    Product* prod =  creators[i]->DoMakeProduct();
    cout << prod->getName() << endl;
    delete prod;
  }
}
