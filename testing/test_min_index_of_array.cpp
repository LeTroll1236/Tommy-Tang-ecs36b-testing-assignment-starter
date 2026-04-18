#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */
    int ar[] = {1, 4, 7, 9};
    int len = 4;

    EXPECT_EQ(min_index_of_array(ar, len), 0);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */
    int ar[] = {8, 6, 5, 2};
    int len = 4;

    EXPECT_EQ(min_index_of_array(ar, len), 3);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */
    int ar[] = {10, 3, 12, 15};
    int len = 4;

    EXPECT_EQ(min_index_of_array(ar, len), 1);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */
    int ar[] = {5, 2, 7, 2, 9};
    int len = 5;

    EXPECT_EQ(min_index_of_array(ar, len), 1);
}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    int ar[] = {6, 4, 8, 1, 3};
    int original[] = {6, 4, 8, 1, 3};
    int len = 5;

    min_index_of_array(ar, len);

    for (int i = 0; i < len; i++) {
        EXPECT_EQ(ar[i], original[i]);
    }
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              ()) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */
    std::vector<int> values = *rc::gen::nonEmpty<std::vector<int>>();
    int* ar = values.data();
    int len = values.size();

    int min_index = min_index_of_array(ar, len);

    RC_ASSERT(min_index >= 0);
    RC_ASSERT(min_index < len);

    for (int i = 0; i < len; i++) {
        RC_ASSERT(ar[min_index] <= ar[i]);
    }
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              ()) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    std::vector<int> values = *rc::gen::nonEmpty<std::vector<int>>();
    std::vector<int> original = values;

    int* ar = values.data();
    int len = values.size();

    min_index_of_array(ar, len);

    for (int i = 0; i < len; i++) {
        RC_ASSERT(values[i] == original[i]);
    }
}
