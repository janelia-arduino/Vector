// ----------------------------------------------------------------------------
// test_vector.cpp
//
//
// Authors:
// Darsey Litzenberger dlitz@dlitz.net
// ----------------------------------------------------------------------------
#include <unity.h>
#include <Vector.h>

static void test_vector_size() {
  int storage[8] = { 21, 42, 84, 0, 0, 0, 0, 0 };
  Vector<int> v(storage, 3);
  TEST_ASSERT_EQUAL(8, v.max_size());
  TEST_ASSERT_EQUAL(3, v.size());
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  TEST_ASSERT_EQUAL(6, v.size());
  v.pop_back();
  TEST_ASSERT_EQUAL(5, v.size());
}

static void test_vector_iterator() {
  int storage[8] = { 21, 42, 84, 0, 0, 0, 0, 0 };
  Vector<int> v(storage, 3);

  const int expected[3] = { 21, 42, 84 };
  int i=0;
  for (auto it = v.begin(); it != v.end(); ++it, ++i) {
    TEST_ASSERT_EQUAL(expected[i], *it);
  }
  TEST_ASSERT_EQUAL(3, i);
}

static void runTests() {
  UNITY_BEGIN();
  RUN_TEST(test_vector_size);
  RUN_TEST(test_vector_iterator);
  UNITY_END();
}

#ifdef ARDUINO

void setup() {
  runTests();
}

void loop() {
}

#else /* !defined(ARDUINO) */

int main(int argc, char **argv)
{
  runTests();
  return 0;
}

#endif /* !defined(ARDUINO) */
