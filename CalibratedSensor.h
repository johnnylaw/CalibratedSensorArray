#pragma once

#include <Arduino.h>

#define _CALIBRATED_SENSOR_STORE_INTERVAL 16
#define _CALIBRATED_SENSOR_MAXIMUM_VALUE 4095

class Sensor {
public:
  int read();
};

template<int storeCount> class CalibratedSensor : Sensor {

public:
  CalibratedSensor(uint8_t pin, uint8_t initialPosition);

private:
  int _storedReadings[storeCount];
  int _readingCount;
  int _storagePosition;
  int _baseline;
  uint8_t _pin;

public:
  int read();

private:
  void storeReading(int reading);
  void calculateBaseline();

};

template<int storeCount>
CalibratedSensor<storeCount>::CalibratedSensor(uint8_t pin, uint8_t initialPosition) : _pin(pin), _storagePosition(initialPosition) {
  for (int i = 0; i < storeCount; i++) _storedReadings[i] = _CALIBRATED_SENSOR_MAXIMUM_VALUE;
}

template<int storeCount>
int CalibratedSensor<storeCount>::read() {
  _readingCount = (_readingCount + 1) % _CALIBRATED_SENSOR_STORE_INTERVAL;
  int reading = analogRead(_pin);
  if (!_readingCount) storeReading(reading);
  return max(reading - _baseline, 0);
}

// Private

template<int storeCount>
void CalibratedSensor<storeCount>::storeReading(int reading) {
  _storedReadings[_storagePosition++] = reading;
  calculateBaseline();
  _storagePosition %= storeCount;
}

template<int storeCount>
void CalibratedSensor<storeCount>::calculateBaseline() {
  _baseline = _storedReadings[0];
  for (int i = 1; i < storeCount; i++) {
    _baseline = min(_baseline, _storedReadings[i]);
  }
}
