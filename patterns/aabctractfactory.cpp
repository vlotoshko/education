#include "aabctractfactory.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace CreationalPatterns {

class CargoesSpaceShip {
public:
  virtual string info() = 0;
  virtual ~CargoesSpaceShip() {}
};


class PassengerSpaceShip {
public:
  virtual string info() = 0;
  virtual ~PassengerSpaceShip() {}
};


class MilitarySpaceShip {
public:
  virtual string info() = 0;
  virtual ~MilitarySpaceShip() {}
};


class SpeedSpaceShip {
public:
  virtual string info() = 0;
  virtual ~SpeedSpaceShip() {}
};


class SpaceFleetFactory {
public:
  virtual CargoesSpaceShip* createCargoesSpaceShip() = 0;
  virtual PassengerSpaceShip* createPassengerSpaceShip() = 0;
  virtual MilitarySpaceShip* createMilitarySpaceShip() = 0;
  virtual SpeedSpaceShip* createSpeedSpaceShip() = 0;
  virtual ~SpaceFleetFactory() {}
};



class ArtediesCargoes : public CargoesSpaceShip {
public:
  string info() { return "artedies cargoes space ship"; }
};

class ArtediesPassenger : public PassengerSpaceShip {
public:
  string info() { return "artedies passenger space ship"; }
};

class ArtediesMititary : public MilitarySpaceShip {
public:
  string info() { return "artedies military space ship"; }
};

class ArtediesSpeed : public SpeedSpaceShip {
public:
  string info() { return "artedies speed space ship"; }
};


class HarkonanCargoes : public CargoesSpaceShip {
public:
  string info() { return "harkonan cargoes space ship"; }
};

class HarkonanPassenger : public PassengerSpaceShip {
public:
  string info() { return "harkonan passenger space ship"; }
};

class HarkonanMititary : public MilitarySpaceShip {
public:
  string info() { return "harkonan military space ship"; }
};

class HarkonanSpeed : public SpeedSpaceShip {
public:
  string info() { return "harkonan speed space ship"; }
};


class ArtidesFactory : public SpaceFleetFactory {
public:
  CargoesSpaceShip* createCargoesSpaceShip() { return new ArtediesCargoes; };
  PassengerSpaceShip* createPassengerSpaceShip() { return new ArtediesPassenger; };
  MilitarySpaceShip* createMilitarySpaceShip() { return new ArtediesMititary; };
  SpeedSpaceShip* createSpeedSpaceShip() { return new ArtediesSpeed; };
};


class HarkonanFactory : public SpaceFleetFactory {
public:
  CargoesSpaceShip* createCargoesSpaceShip() { return new HarkonanCargoes; };
  PassengerSpaceShip* createPassengerSpaceShip() { return new HarkonanPassenger; };
  MilitarySpaceShip* createMilitarySpaceShip() { return new HarkonanMititary; };
  SpeedSpaceShip* createSpeedSpaceShip() { return new HarkonanSpeed; };
};


class SpaceFleet {
public:
  CargoesSpaceShip* cargoesSpaceShip;
  PassengerSpaceShip* passengerSpaceShip;
  MilitarySpaceShip* militarySpaceShip;
  SpeedSpaceShip* speedSpaceShip;
  SpaceFleet( SpaceFleetFactory& );
  ~SpaceFleet();
};

SpaceFleet::SpaceFleet( SpaceFleetFactory& sFactory ) {
  cargoesSpaceShip = sFactory.createCargoesSpaceShip();
  passengerSpaceShip = sFactory.createPassengerSpaceShip();
  militarySpaceShip = sFactory.createMilitarySpaceShip();
  speedSpaceShip = sFactory.createSpeedSpaceShip();
}

SpaceFleet::~SpaceFleet() {
  delete cargoesSpaceShip;
  delete passengerSpaceShip;
  delete militarySpaceShip;
  delete speedSpaceShip;
}

std::ostream& operator << (std::ostream& out, const SpaceFleet& fleet) {
  out << fleet.cargoesSpaceShip->info() << endl << fleet.passengerSpaceShip->info()
  << endl << fleet.militarySpaceShip->info() << endl << fleet.speedSpaceShip->info() << endl;
  return out;
}

}

void CreationalPatterns::aAbstractFactory() {
  HarkonanFactory harFactory;
  ArtidesFactory artFactory;

  SpaceFleet harFleet( harFactory );
  SpaceFleet artFleet( artFactory );
  cout << artFleet << endl;
  cout << harFleet << endl;
}
