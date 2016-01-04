#include "Arduino.h"
#include "Streaming.h"
#include "Vector.h"


const int BAUDRATE = 9600;

const int ELEMENT_COUNT_MAX = 5;

void printVector(Vector<int> vector)
{
  Serial << "[";
  for (int i=0; i<vector.size(); i++)
  {
    if (i != 0)
    {
      Serial << ",";
    }
    Serial << vector[i];
  }
  Serial << "]" << endl << endl;
}

void setup()
{
  Serial.begin(BAUDRATE);
  delay(1000);

  int storage_array[ELEMENT_COUNT_MAX];
  Vector<int> vector;
  vector.setStorageArray(storage_array);
  Serial << "vector.max_size(): " << vector.max_size() << endl;
  Serial << "vector.size(): " << vector.size() << endl;
  Serial << "vector:" << endl;
  printVector(vector);

  vector.push_back(10);
  vector.push_back(8);
  vector.push_back(7);
  Serial << "vector.max_size(): " << vector.max_size() << endl;
  Serial << "vector.size(): " << vector.size() << endl;
  Serial << "vector:" << endl;
  printVector(vector);

  int storage_array2[ELEMENT_COUNT_MAX];
  Vector<int> vector2(storage_array2);
  vector2.push_back(1);
  vector2.push_back(2);
  vector2.push_back(4);
  vector2.pop_back();
  Serial << "vector2.max_size(): " << vector2.max_size() << endl;
  Serial << "vector2.size(): " << vector2.size() << endl;
  Serial << "vector2:" << endl;
  printVector(vector2);

  int storage_array3[ELEMENT_COUNT_MAX];
  storage_array3[0] = 3;
  storage_array3[1] = 5;
  Vector<int> vector3(storage_array3);
  Serial << "vector3.max_size(): " << vector3.max_size() << endl;
  Serial << "vector3.size(): " << vector3.size() << endl;
  Serial << "vector3:" << endl;
  printVector(vector3);

  int storage_array4[ELEMENT_COUNT_MAX];
  storage_array4[0] = 3;
  storage_array4[1] = 5;
  Vector<int> vector4(storage_array4,2);
  Serial << "vector4.max_size(): " << vector4.max_size() << endl;
  Serial << "vector4.size(): " << vector4.size() << endl;
  Serial << "vector4:" << endl;
  printVector(vector4);
}


void loop()
{
}
