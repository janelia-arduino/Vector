#include "Arduino.h"
#include "Streaming.h"
#include "Vector.h"


const unsigned int BAUDRATE = 9600;
const unsigned int MAX_SIZE = 10;

Vector<int, MAX_SIZE> array;

void printVector(Vector<int,MAX_SIZE> array)
{
  Serial << "array = [";
  for (int i=0; i<array.size(); i++)
  {
    if (i != 0)
    {
      Serial << ",";
    }
    Serial << array[i];
  }
  Serial << "]" << endl;
}

void setup()
{
  Serial.begin(BAUDRATE);
  delay(1000);

  printVector(array);
  Serial << "array.max_size() = " << array.max_size() << endl;
  Serial << "array.size() = " << array.size() << endl;
  Serial << "array.empty() = " << array.empty() << endl;
  Serial << "array.full() = " << array.full() << endl;
  Serial << endl;

  const int simple_size = 3;
  int array_simple[simple_size] = {8,9,10};
  array.assign(simple_size,array_simple);

  printVector(array);
  Serial << "array.max_size() = " << array.max_size() << endl;
  Serial << "array.size() = " << array.size() << endl;
  Serial << "array.empty() = " << array.empty() << endl;
  Serial << "array.full() = " << array.full() << endl;
  Serial << endl;

  array.push_back(39);
  array.push_back(73);
  printVector(array);
  Serial << "array.size() = " << array.size() << endl;
  Serial << "array.front() = " << array.front() << endl;
  Serial << "array.back() = " << array.back() << endl;
  Serial << endl;

  array.pop_back();
  array.pop_back();
  array.pop_back();
  printVector(array);
  Serial << "array.size() = " << array.size() << endl;
  Serial << "array.front() = " << array.front() << endl;
  Serial << "array.back() = " << array.back() << endl;
  Serial << endl;

  array.clear();
  Serial << "array.size() = " << array.size() << endl;
  Serial << "array.front() = " << array.front() << endl;
  Serial << "array.back() = " << array.back() << endl;
  Serial << endl;
}


void loop()
{
}
