#include "aprototype.h"
#include <iostream>
#include <map>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::endl;


namespace CreationalPatterns {


namespace PrototypeIDVariant {

enum Warrior_ID {Infantryman_ID, Archer_ID, Horseman_ID };

class Warrior; // forward declaration
typedef std::map< Warrior_ID, Warrior* > Registry;

Registry& getRegistry() {
  static Registry instance;
  return instance;
}


class Dummy{};

class Warrior {
public:
  virtual Warrior* clone() = 0;
  virtual string info() = 0;
  virtual ~Warrior() {}
  static Warrior* createWarrior( Warrior_ID id ) {
    Registry& r = getRegistry();
    if( r.find(id) != r.end() )
      return r[id]->clone();
    return 0;
  }
protected:
  static void addProtopype( Warrior_ID id, Warrior* prototype) {
    Registry& r = getRegistry();
    r[id] = prototype;
  }
  static void removePrototype( Warrior_ID id ) {
    Registry& r = getRegistry();
    r.erase( r.find( id ) );
  }
};


class Infantryman : public Warrior {
public:
  Warrior* clone() {
    return new Infantryman( * this );
  }
  string info() {
    return "Infantryman";
  }
private:
  Infantryman( Dummy ) {
    Warrior::addProtopype( Infantryman_ID, this );
  }
  Infantryman() {}
  static Infantryman prototype;
};


class Archer : public Warrior {
public:
  Warrior* clone() {
    return new Archer( * this );
  }
  string info() {
    return "Archer";
  }
private:
  Archer( Dummy ) {
    Warrior::addProtopype( Archer_ID, this );
  }
  Archer() {}
  static Archer prototype;
};


class Horseman : public Warrior {
public:
  Warrior* clone() {
    return new Horseman( * this );
  }
  string info() {
    return "Horseman";
  }
private:
  Horseman( Dummy ) {
    Warrior::addProtopype( Horseman_ID, this );
  }
  Horseman() {}
  static Horseman prototype;
};

Infantryman Infantryman::prototype = Infantryman( Dummy() );
Archer Archer::prototype = Archer( Dummy() );
Horseman Horseman::prototype = Horseman( Dummy() );



void aPrototype() {
  std::vector< Warrior* > v;
  v.push_back( Warrior::createWarrior( Infantryman_ID ) );
  v.push_back( Warrior::createWarrior( Archer_ID ) );
  v.push_back( Warrior::createWarrior( Horseman_ID ) );
  for( size_t i = 0; i < v.size(); ++i )
    cout << v[i]->info() << endl;
}

}




namespace PrototypeFactoryVariant {

class Warrior {
public:
  virtual Warrior* clone() = 0;
  virtual string info() = 0;
  ~Warrior() {}
};


class Infantryman : public Warrior {
  friend class PrototypeFactory;
public:
  Warrior* clone() {
    return new Infantryman( *this );
  }
  string info() {
    return "Infantryman";
  }
private:
  Infantryman() {}
};

class Archer : public Warrior {
  friend class PrototypeFactory;
public:
  Warrior* clone() {
    return new Archer( *this );
  }
  string info() {
    return "Archer";
  }
private:
  Archer() {}
};

class Horseman : public Warrior {
  friend class PrototypeFactory;
public:
  Warrior* clone() {
    return new Horseman( *this );
  }
  string info() {
    return "Horseman";
  }
private:
  Horseman() {}
};



class PrototypeFactory {
public:
  Warrior* createInfantryman() {
    static Infantryman prototype;
    return prototype.clone();
  }
  Warrior* createArcher() {
    static Archer prototype;
    return prototype.clone();
  }
  Warrior* createHorseman() {
    static Horseman prototype;
    return prototype.clone();
  }
};


void aPrototype() {
  PrototypeFactory factory;
  std::vector< Warrior* > v;
  v.push_back( factory.createInfantryman() );
  v.push_back( factory.createArcher() );
  v.push_back( factory.createHorseman() );
  for( size_t i = 0; i < v.size(); ++i )
    cout << v[i]->info() << endl;
}

}


}

void CreationalPatterns::aPrototype() {
  PrototypeIDVariant::aPrototype();
}

void CreationalPatterns::aPrototype2() {
  PrototypeFactoryVariant::aPrototype();
}
