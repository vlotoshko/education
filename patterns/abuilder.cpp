#include "abuilder.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace CreationalPatterns {

class Infantryman {
public:
  string info() { return "Infantryman"; }
};


class Archer {
public:
  string info() { return "Archer"; }
};


class Horseman {
public:
  string info() { return "Horseman"; }
};


class Catapult {
public:
  string info() { return "Catapult"; }
};


class Elephant {
public:
  string info() { return "Elephant"; }
};


// Class includes all army units
class Army {
public:
  Army() : infantryman( 0 ), archer ( 0 ), horseman( 0 ), catapult( 0 ), elephant( 0 ) {}
  ~Army();
  Infantryman* infantryman;
  Archer* archer;
  Horseman* horseman;
  Catapult* catapult;
  Elephant* elephant;
  string info() const ;
};


Army::~Army() {
  if( infantryman != 0 ) delete infantryman;
  if( archer != 0 ) delete archer;
  if( horseman != 0 ) delete horseman;
  if( catapult != 0 ) delete catapult;
  if( elephant != 0 ) delete elephant;
}

string Army::info() const {
  return ( ( infantryman != 0 ) ? infantryman->info() + '\n' : "" )
    + ( ( archer != 0 ) ? archer->info() + '\n' : "" )
    + ( ( horseman != 0 ) ? horseman->info() + '\n' : "" )
    + ( ( catapult != 0 ) ? catapult->info() + '\n' : "" )
    + ( ( elephant != 0 ) ? elephant->info() + '\n' : "" );
}



std::ostream& operator<< (std::ostream& out, const Army& army ) {
  out << army.info();
  return out;
}


class ArmyBuilder {
protected:
  Army* p;
public:
  ArmyBuilder() : p( 0 ) {}
  ~ArmyBuilder() {}
  virtual void createArmy() {}
  virtual void buildInfantryman() {}
  virtual void buildArcher() {}
  virtual void buildHorseman() {}
  virtual void buildCatapult() {}
  virtual void buildElephant() {}
  virtual Army* getArmy() { return p; }
};


class RomeArmyBuilder : public ArmyBuilder {
public:
  void createArmy() { p = new Army; }
  void buildInfantryman() { p->infantryman = new Infantryman(); }
  void buildArcher() { p->archer = new Archer(); }
  void buildHorseman() { p->horseman = new Horseman(); }
  void buildCatapult() { p->catapult = new Catapult(); }
};


class CarfagenArmyBuilder : public ArmyBuilder {
public:
  void createArmy() { p = new Army; }
  void buildInfantryman() { p->infantryman = new Infantryman(); }
  void buildArcher() { p->archer = new Archer();}
  void buildHorseman() { p->horseman = new Horseman(); }
  void buildElephant() { p->elephant = new Elephant(); }
};


class ArmyDirector {
public:
  Army* createArmy( ArmyBuilder& builder ) {
    builder.createArmy();
    builder.buildInfantryman();
    builder.buildArcher();
    builder.buildHorseman();
    builder.buildCatapult();
    builder.buildElephant();
    return builder.getArmy();
  }
};

}

void CreationalPatterns::aBuilder() {
  RomeArmyBuilder romeBuilder;
  CarfagenArmyBuilder carfagenBuilder;
  ArmyDirector dir;

  Army* ra = dir.createArmy( romeBuilder );
  Army* ca = dir.createArmy( carfagenBuilder );
  cout << "Rome army:\n" << *ra << endl;
  cout << "Carthaginian army:\n" << *ca << endl << endl;

  delete ra;
  delete ca;
}
