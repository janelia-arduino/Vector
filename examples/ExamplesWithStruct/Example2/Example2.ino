/*
    In any case if you need to allocate structs in the heap, this example can be useful.
*/
#include <Arduino.h>
#include <Streaming.h>
#include <Vector.h>

#define EasyMalloc(type, size) ((type *)malloc(sizeof(type) * size))

struct DataPackage {
  int id;
  int value;
};

const long BAUD = 115200;
const int ELEMENT_COUNT_MAX = 10;
typedef Vector<DataPackage *> DataPackageVector;
const unsigned int DELAY = 2500;

DataPackageVector dataPackageVector;

void AddDataPackage(int id, int value) {
  DataPackage *dataPackage = EasyMalloc(struct DataPackage, 1);
  dataPackage->id = id;
  dataPackage->value = value;
  dataPackageVector.push_back(dataPackage);
}

void RemoveDataPackage(int id) {
  for (int i = 0; i < dataPackageVector.size(); i++) {
    if (dataPackageVector[i]->id == id) {
      free(dataPackageVector[i]);
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
  unsigned int counter = 0;
  for (DataPackage *dataPackage : dataPackageVector) {
    Serial << counter << "-> " << "id: " << dataPackage->id << " value: " << dataPackage->value << endl;
    counter++;
  }
}

// if given id is not found in the data package vector, return false
bool FindDataPackage(int id) {
  for (DataPackage *dataPackage : dataPackageVector) {
    if (dataPackage->id == id) {
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

  dataPackageVector.setStorage(
      EasyMalloc(struct DataPackage *, ELEMENT_COUNT_MAX), // allocated memory
      ELEMENT_COUNT_MAX, // max size of the vector
      0                  // current size of the vector
  );
}

void loop() {
  // pick a random number as id between 0 and 10
  // if it is not already in the vector, add it
  // if it is in the vector, remove it
  unsigned int id = random(0, 10);

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
    // print added data package
    Serial << "Added data package with id: " << id << " value: " << value << endl;
  }
  // print the data package vector
  PrintDataPackageVector();
  Serial << "------------------------------" << endl;
  delay(DELAY);
}