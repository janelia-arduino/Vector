#Vector

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

A sequence container similar to the C++
[std::vector](http://www.cplusplus.com/reference/vector/vector/), but
instead of allocating memory dynamically, this container points to an
external, statically allocated c style array. The maximum size is
fixed at compile time, but the size can change by pushing and popping
elements from the vector. Static memory allocation is used to avoid
dynamic allocation problems on very small embedded processors. Care
must be taken not to dereference an empty vector, access elements
beyond bounds, or use without setting the storage array.

This library is very similar to
[Array](https://github.com/janelia-arduino/Array), however Array
stores data internally in the container and this library stores data
externally. The pointer to the external memory causes this container
to use more memory than the Array container, but storing the data
externally avoids needing the maximum size as a class template
parameter.

## Vector vs Array

###Vector

```c++
const int ELEMENT_COUNT = 5;
int storage_array[ELEMENT_COUNT_MAX];
Vector<int> vector(storage_array);
vector.push_back(77);
```

###Array

```c++
const int ELEMENT_COUNT = 5;
Array<int,ELEMENT_COUNT> array;
array.push_back(77);
```

[Usage Examples](./examples)

##Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
