#pragma once

#include <Arduino.h>
#include <CalibratedSensor.h>

template<int storeCount, uint8_t aggregateSize> class CalibratedSensorArray {

public:
  CalibratedSensorArray(CalibratedSensor<storeCount> *array, uint8_t size);

private:
  Sensor *_array;
  uint8_t _size;
  int _aggregate[aggregateSize];

public:
  int readMax();

private:
  void resetAggregate(int value);
  uint8_t positionOfMin();
  int sum();

};

template<int storeCount, uint8_t aggregateSize>
CalibratedSensorArray<storeCount, aggregateSize>::CalibratedSensorArray(CalibratedSensor<storeCount> *array, uint8_t size) : _array(array), _size(size) {}

template<int storeCount, uint8_t aggregateSize>
int CalibratedSensorArray<storeCount, aggregateSize>::readMax() {
  resetAggregate(0);
  for (int i = 0; i < _size; i++) {
    uint8_t position = positionOfMin();
    int value = _array[i].read();
    if (value > _aggregate[i]) _aggregate[i] = value;
  }
  return sum();
}

template<int storeCount, uint8_t aggregateSize>
void CalibratedSensorArray<storeCount, aggregateSize>::resetAggregate(int value) {
  for (int i = 0; i < aggregateSize; i++) _aggregate[i] = value;
}

template<int storeCount, uint8_t aggregateSize>
uint8_t CalibratedSensorArray<storeCount, aggregateSize>::positionOfMin() {
  uint8_t position = 0;
  for (int i = 1; i < aggregateSize; i++) {
    if (_aggregate[i] < _aggregate[position]) position = i;
  }
  return position;
}

template<int storeCount, uint8_t aggregateSize>
int CalibratedSensorArray<storeCount, aggregateSize>::sum() {
  int result = _aggregate[0];
  for (int i = 1; i < aggregateSize; i++) result += _aggregate[i];
  return result;
}
