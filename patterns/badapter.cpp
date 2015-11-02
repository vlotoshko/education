#include "badapter.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

namespace StructuralPatterns {


class FahrenheitSensor {
public:
  float getTemperature() {
    float t = 50.0;
    // ... imagine some code here
    return t;
  }
};

class Sensor {
public:
  virtual float getTemperature() = 0;
  virtual ~Sensor() {}
};


class Adapter : public Sensor {
public:
  Adapter( FahrenheitSensor* f) : _fsensor( f ) {}
  ~Adapter() {
    delete _fsensor;
  }
  float getTemperature() {
    return (_fsensor->getTemperature()-32.0)*5.0/9.0;
  }
private:
  FahrenheitSensor* _fsensor;
};


class FahrenheitSensor2
{
  public:
    float getTemperature() {
      float t = 51.0;
      // ...
      return t;
    }
  protected:
    void adjust() {} // Настройка датчика (защищенный метод)
};


class Sensor2  {
  public:
    virtual ~Sensor2() {}
    virtual float getTemperature() = 0;
    virtual void adjust() = 0;
};


class Adapter2 : public Sensor2, private FahrenheitSensor2 {
  public:
    Adapter2() { }
    float getTemperature() {
      return (FahrenheitSensor2::getTemperature()-32.0)*5.0/9.0;
    }
    void adjust() {
      FahrenheitSensor2::adjust();
    }
};

}

void StructuralPatterns::bAdapter() {
  Adapter* a = new Adapter( new FahrenheitSensor() );
  cout << a->getTemperature() << endl;

  Adapter2* b = new Adapter2();
  b->adjust();
  cout << b->getTemperature() << endl;

  delete a;
  delete b;
}
