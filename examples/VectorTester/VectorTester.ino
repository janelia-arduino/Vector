#include <Arduino.h>
#include <Streaming.h>
#include <Vector.h>


const long BAUD = 115200;

const int ELEMENT_COUNT_MAX = 5;

void setup()
{
  Serial.begin(BAUD);
  delay(1000);

}

void loop()
{
  int storage_array[ELEMENT_COUNT_MAX];
  Vector<int> vector;
  vector.setStorage(storage_array);
  Serial << "vector.max_size(): " << vector.max_size() << endl;
  Serial << "vector.size(): " << vector.size() << endl;
  Serial << "vector:" << endl;
  Serial << vector << endl;
  delay(1000);

  vector.push_back(10);
  vector.push_back(8);
  vector.push_back(7);
  Serial << "vector.max_size(): " << vector.max_size() << endl;
  Serial << "vector.size(): " << vector.size() << endl;
  Serial << "vector:" << endl;
  Serial << vector << endl;
  vector.remove(0);
  Serial << "vector.remove(0):" << endl;
  Serial << vector << endl;
  vector.remove(1);
  Serial << "vector.remove(1):" << endl;
  Serial << vector << endl;
  delay(1000);

  int storage_array2[ELEMENT_COUNT_MAX];
  Vector<int> vector2(storage_array2);
  vector2.push_back(1);
  vector2.push_back(2);
  vector2.push_back(4);
  vector2.pop_back();
  Serial << "vector2.max_size(): " << vector2.max_size() << endl;
  Serial << "vector2.size(): " << vector2.size() << endl;
  Serial << "vector2:" << endl;
  Serial << vector2 << endl;
  delay(1000);

  int storage_array3[ELEMENT_COUNT_MAX];
  storage_array3[0] = 3;
  storage_array3[1] = 5;
  Vector<int> vector3(storage_array3);
  Serial << "vector3.max_size(): " << vector3.max_size() << endl;
  Serial << "vector3.size(): " << vector3.size() << endl;
  Serial << "vector3:" << endl;
  Serial << vector3 << endl;
  delay(1000);

  int storage_array4[ELEMENT_COUNT_MAX];
  storage_array4[0] = 3;
  storage_array4[1] = 5;
  Vector<int> vector4(storage_array4,2);
  Serial << "vector4.max_size(): " << vector4.max_size() << endl;
  Serial << "vector4.size(): " << vector4.size() << endl;
  Serial << "vector4:" << endl;
  Serial << vector4 << endl;
  delay(1000);

  int storage_array5[1];
  Vector<int> vector5(storage_array5);
  Serial << "vector5.max_size(): " << vector5.max_size() << endl;
  Serial << "vector5.size(): " << vector5.size() << endl;
  Serial << "vector5:" << endl;
  Serial << vector5 << endl;
  delay(1000);

  int storage_array6[ELEMENT_COUNT_MAX];
  Vector<int> vector6(storage_array6);
  vector6.assign(ELEMENT_COUNT_MAX-1,8);
  Serial << "vector6:" << endl;
  Serial << vector6 << endl;
  delay(1000);
}
