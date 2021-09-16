#ifdef ARDUINO
# include <Arduino.h>
#else
# include <cstdio>
#endif

#include <Vector.h>

char storage[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\r', '\n' };
Vector<char> vector(storage, sizeof(storage));

#ifdef ARDUINO

void setup() {
  Serial.begin(115200);
  Serial.println("Starting up.");
}

void loop() {
  Serial.print("Vector size is ");
  Serial.println(vector.size());

  Serial.print("Vector content: ");
  for (unsigned int i = 0; i < vector.size(); i++) {
    Serial.print(vector.at(i));
  }

  delay(2000);
}

#else /* !defined(ARDUINO) */

int main(int argc, char **argv) {
  puts("Starting up.");
  printf("Vector size is %d\n", vector.size());

  printf("Vector content: ");
  for (unsigned int i = 0; i < vector.size(); i++) {
    putchar(vector.at(i));
  }

  return 0;
}

#endif
