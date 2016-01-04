#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace constants
{
enum {X_SIZE=1};
enum {Y_SIZE=2};
enum {Z_SIZE=3};

enum {RESERVED_X_COUNT=3};
enum {RESERVED_Y_COUNT=0};
enum {RESERVED_Z_COUNT=1};

extern const unsigned int baudrate;

extern const int x_default[X_SIZE];
extern const int y_default[Y_SIZE];
extern const int z_default[Z_SIZE];
}
#endif
