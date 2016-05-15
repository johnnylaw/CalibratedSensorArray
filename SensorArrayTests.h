#include <SensorArray.h>
#include <ArduinoUnit.h>

class SensorSubclass : public Sensor {
public:
  SensorSubclass(int value) : _value(value) {};

private:
  int _value;

public:
  int read() { return _value; };
};

test(SensorArray_readMax_1Sensor_1Considered) {
  SensorSubclass sensors[1] = { 3098 };
  SensorArray<SensorSubclass, 1> array = SensorArray<SensorSubclass, 1>(sensors, 1);
  assertEqual(array.readMax(), 3098);
}

test(SensorArray_readMax_2Sensor_1Considered) {
  SensorSubclass sensors[2] = { 3098, 2092 };
  SensorArray<SensorSubclass, 1> array = SensorArray<SensorSubclass, 1>(sensors, 2);
  assertEqual(array.readMax(), 3098);
}

test(SensorArray_readMax_2Sensor_1Considered_HighestLast) {
  SensorSubclass sensors[2] = { 2092, 3098 };
  SensorArray<SensorSubclass, 1> array = SensorArray<SensorSubclass, 1>(sensors, 2);
  assertEqual(array.readMax(), 3098);
}

test(SensorArray_readMax_4Sensor_2Considered) {
  SensorSubclass sensors[4] = { 55, 2092, 3098, 255 };
  SensorArray<SensorSubclass, 2> array = SensorArray<SensorSubclass, 2>(sensors, 4);
  assertEqual(array.readMax(), 3098 + 2092);
}
