#include <cassert>

struct VectorAccessFailure {};

#define VECTOR_ACCESS_CHECK(condition)                                        \
  do {                                                                        \
    if (!(condition)) {                                                       \
      throw VectorAccessFailure{};                                            \
    }                                                                         \
  } while (0)

#include <Vector.h>

namespace {

void test_vector_invalid_access_throws_when_hook_enabled() {
  Vector<int> vector;

  bool threw = false;
  try {
    static_cast<void>(vector.front());
  } catch (const VectorAccessFailure &) {
    threw = true;
  }
  assert(threw);

  int storage[2] = {1, 2};
  vector.setStorage(storage, 1);

  threw = false;
  try {
    static_cast<void>(vector.at(1));
  } catch (const VectorAccessFailure &) {
    threw = true;
  }
  assert(threw);
}

void test_vector_valid_access_still_works_with_hook_enabled() {
  int storage[3] = {10, 20, 30};
  Vector<int> vector(storage, 3);

  assert(vector.front() == 10);
  assert(vector.back() == 30);
  assert(vector.at(1) == 20);
  assert(vector[2] == 30);
}

} // namespace

int main() {
  test_vector_invalid_access_throws_when_hook_enabled();
  test_vector_valid_access_still_works_with_hook_enabled();
  return 0;
}
