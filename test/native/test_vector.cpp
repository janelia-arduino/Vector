#include <cassert>
#include <cstddef>

#include <Vector.h>

namespace {

void test_default_vector_requires_storage() {
  Vector<int> vector;
  assert(vector.size() == 0);
  assert(vector.max_size() == 0);
  assert(vector.empty());
  assert(vector.full());

  vector.push_back(7);
  assert(vector.size() == 0);
}

void test_attach_storage_and_capacity_limits() {
  int storage[4] = {};
  Vector<int> vector(storage, 99);
  assert(vector.max_size() == 4);
  assert(vector.size() == 4);
  assert(vector.full());
  vector.clear();
  assert(vector.empty());
  assert(!vector.full());

  vector.push_back(10);
  vector.push_back(20);
  vector.push_back(30);
  vector.push_back(40);
  vector.push_back(50);

  assert(vector.size() == 4);
  assert(vector.full());
  assert(vector.front() == 10);
  assert(vector.back() == 40);
}

void test_set_storage_pointer_path_and_invalid_setup() {
  int storage[3] = {9, 8, 7};
  Vector<int> vector;

  vector.setStorage(storage, 3, 5);
  assert(vector.data() == storage);
  assert(vector.max_size() == 3);
  assert(vector.size() == 3);
  assert(vector.front() == 9);
  assert(vector.back() == 7);

  vector.setStorage(nullptr, 4, 2);
  assert(vector.data() == nullptr);
  assert(vector.max_size() == 0);
  assert(vector.size() == 0);
  assert(vector.empty());
  assert(vector.full());

  vector.push_back(11);
  assert(vector.size() == 0);
}

void test_assign_fill_and_remove() {
  int storage[5] = {};
  Vector<int> vector(storage);

  vector.fill(3);
  assert(vector.size() == 5);
  assert(vector[0] == 3);
  assert(vector[4] == 3);

  const int values[] = {1, 2, 3};
  vector.assign(3, values);
  assert(vector.size() == 3);
  assert(vector[0] == 1);
  assert(vector[2] == 3);

  vector.remove(1);
  assert(vector.size() == 2);
  assert(vector[0] == 1);
  assert(vector[1] == 3);

  vector.pop_back();
  assert(vector.size() == 1);
  vector.clear();
  assert(vector.empty());
}

void test_cross_type_assignment_and_truncation() {
  int storage[3] = {};
  Vector<int> vector(storage);

  const long source_values[] = {100L, 200L, 300L, 400L};
  vector.assign(4, source_values);
  assert(vector.size() == 3);
  assert(vector[0] == 100);
  assert(vector[1] == 200);
  assert(vector[2] == 300);

  long source_storage[4] = {7L, 8L, 9L, 10L};
  Vector<long> source(source_storage, 4);
  vector.assign(4, source);
  assert(vector.size() == 3);
  assert(vector[0] == 7);
  assert(vector[1] == 8);
  assert(vector[2] == 9);
}

void test_iteration_and_data_access() {
  int storage[4] = {5, 6, 7, 0};
  Vector<int> vector(storage, 3);

  int sum = 0;
  for (auto value : vector) {
    sum += value;
  }
  assert(sum == 18);

  int *data = vector.data();
  assert(data == storage);
  data[1] = 42;
  assert(vector.at(1) == 42);
}

void test_const_accessors_and_iterator_identity() {
  int storage_a[3] = {1, 2, 3};
  int storage_b[3] = {1, 2, 3};
  const Vector<int> vector(storage_a, 3);
  const Vector<int> other(storage_b, 3);

  assert(vector.front() == 1);
  assert(vector.back() == 3);
  assert(vector.begin() != other.begin());
}

} // namespace

int main() {
  test_default_vector_requires_storage();
  test_attach_storage_and_capacity_limits();
  test_set_storage_pointer_path_and_invalid_setup();
  test_assign_fill_and_remove();
  test_cross_type_assignment_and_truncation();
  test_iteration_and_data_access();
  test_const_accessors_and_iterator_identity();
  return 0;
}
