#include "Arduino.h"
#include "Streaming.h"
#include "Vector.h"
#include "Constants.h"
#include "Device.h"


void setup()
{
  Device<int,
         constants::X_SIZE,
         constants::Y_SIZE,
         constants::Z_SIZE> device;

  Serial.begin(constants::baudrate);
  delay(1000);

  Serial << "device:" << endl;
  device.print();

  device.printRandomObject(3.1415);
}


void loop()
{
}
