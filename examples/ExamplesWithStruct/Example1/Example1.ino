/*
  If you want to use this library with structs, this exapmle can be useful.
*/
#include <Arduino.h>
#include <Streaming.h>
#include <Vector.h>

struct DataPackage {
  int id;
  int value;
};

const long BAUD = 115200;
const int ELEMENT_COUNT_MAX = 10;
typedef Vector<DataPackage> DataPackageVector;
const size_t DELAY = 2500;


DataPackage storage_array[ELEMENT_COUNT_MAX];
DataPackageVector dataPackageVector;

void AddDataPackage(int id, int value) {
  DataPackage dataPackage;
  dataPackage.id = id;
  dataPackage.value = value;
  dataPackageVector.push_back(dataPackage);
}

void RemoveDataPackage(int id) {
  for (int i = 0; i < dataPackageVector.size(); i++) {
    if (dataPackageVector[i].id == id) {
      dataPackageVector.remove(i);
      break;
    }
  }
}

void PrintDataPackageVector() {
  if (dataPackageVector.empty()) {
    Serial << "DataPackageVector is empty" << endl;
    return;
  }
  Serial << "DataPackageVector size: " << dataPackageVector.size() << endl;
  size_t counter = 0;
  for (DataPackage dataPackage : dataPackageVector) {
    Serial << counter << "-> " << "id: " << dataPackage.id << " value: " << dataPackage.value << endl;
    counter++;
  }
}

// if given id is not found in the data package vector, return false
bool FindDataPackage(int id) {
  for (DataPackage dataPackage : dataPackageVector) {
    if (dataPackage.id == id) {
      dataPackage = dataPackage;
      return true;
    }
  }
  return false;
}

void setup() {
  Serial.begin(BAUD);
  while (!Serial) {
    // wait for serial port to connect.
  }

  dataPackageVector.setStorage(storage_array, 0);
}

void loop() {
  // pick a random number as id between 0 and 10
  // if it is not already in the vector, add it
  // if it is in the vector, remove it
  size_t id = random(0, 10);

  if (FindDataPackage(id)) {
    // remove the data package
    RemoveDataPackage(id);
    // print removed data package
    Serial << "Removed data package with id: " << id << endl;
  } else {
    // choose a random number between 0 and 100
    int value = random(0, 100);
    // add the data package
    AddDataPackage(id, value);
    // print added data package id and value
    Serial << "Added data package with id: " << id << " value: " << value << endl;
  }
  // print the data package vector
  PrintDataPackageVector();
  Serial << "------------------------------" << endl;
  delay(DELAY);
}