#include <CalibratedSensor.h>
#include <ArduinoUnit.h>


class SensorSubclass : public Sensor {
public:
  SensorSubclass(int value) : _value(value) {};

private:
  int _value;

public:
  int read() { return _value; };
};

class CalibratedSensorArrayTests {
// public:
//   CalibratedSensorArrayTests();

private:

public:
  void testReadMax_1Sensor_1Considered();
};

void CalibratedSensorArrayTests::testReadMax_1Sensor_1Considered() {
  SensorSubclass sensors[1] = { 3098 };
  CalibratedSensorArray<SensorSubclass, 1> array = CalibratedSensorArray<SensorSubclass, 1>(sensors, 1);
  assertEqual(array.readMax(), 3098);
}

// void CalibratedSensorArrayTests::testReadMax_1Sensor_1Considered() {
//   SensorSubclass sensors[1] = { 3098 };
//   CalibratedSensorArray<SensorSubclass, 1> array = CalibratedSensorArray<SensorSubclass, 1>(sensors, 1);
//   assertEqual(array.readMax(), 3098);
// }