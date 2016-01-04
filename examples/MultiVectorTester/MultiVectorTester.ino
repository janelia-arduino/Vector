#include "Arduino.h"
#include "Streaming.h"
#include "Vector.h"
#include "Constants.h"
#include "MultiVector.h"
#include "TemplatedMultiVector.h"


MultiVector multi_array;
TemplatedMultiVector<int,
                    constants::X_SIZE,
                    constants::Y_SIZE,
                    constants::Z_SIZE> templated_multi_array;

void setup()
{
  Serial.begin(constants::baudrate);
  delay(1000);

  Serial << "multi_array:" << endl;
  multi_array.print();

  Serial << "templated_multi_array:" << endl;
  templated_multi_array.print();
}


void loop()
{
}
