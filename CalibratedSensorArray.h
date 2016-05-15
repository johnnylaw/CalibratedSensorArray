#pragma once

#include <Arduino.h>
#include <CalibratedSensor.h>

template<class T, uint8_t aggregateSize> class CalibratedSensorArray {

public:
  CalibratedSensorArray(T *sensors, uint8_t size);

private:
  T *_sensors;
  uint8_t _size;
  int _aggregate[aggregateSize];

public:
  int readMax();

private:
  void resetAggregate(int value);
  uint8_t positionOfMin();
  int sum();

};

template<class T, uint8_t aggregateSize>
CalibratedSensorArray<T, aggregateSize>::CalibratedSensorArray(T *sensors, uint8_t size) : _sensors(sensors), _size(size) {}

template<class T, uint8_t aggregateSize>
int CalibratedSensorArray<T, aggregateSize>::readMax() {
  resetAggregate(0);
  for (int i = 0; i < _size; i++) {
    uint8_t position = positionOfMin();
    int value = _sensors[i].read();
    if (value > _aggregate[i]) _aggregate[i] = value;
  }
  return sum();
}

template<class T, uint8_t aggregateSize>
void CalibratedSensorArray<T, aggregateSize>::resetAggregate(int value) {
  for (int i = 0; i < aggregateSize; i++) _aggregate[i] = value;
}

template<class T, uint8_t aggregateSize>
uint8_t CalibratedSensorArray<T, aggregateSize>::positionOfMin() {
  uint8_t position = 0;
  for (int i = 1; i < aggregateSize; i++) {
    if (_aggregate[i] < _aggregate[position]) position = i;
  }
  return position;
}

template<class T, uint8_t aggregateSize>
int CalibratedSensorArray<T, aggregateSize>::sum() {
  int result = _aggregate[0];
  for (int i = 1; i < aggregateSize; i++) result += _aggregate[i];
  return result;
}
