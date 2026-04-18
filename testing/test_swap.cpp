#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = 1, b = 2;
    swap(&a, &b);
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 1);
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */
    int arr[] = {1, 2, 3, 4, 5};

    swap(&arr[1], &arr[3]);

    EXPECT_EQ(arr[1], 4);
    EXPECT_EQ(arr[3], 2);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[4], 5);
}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = a_start;
    int b = b_start;

    swap(&a, &b);

    RC_ASSERT(a == b_start);
    RC_ASSERT(b == a_start);
}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */
    RC_PRE(values.size() >= 2u);  // need at least two elements

    std::vector<int> arr = values;

    int i = *rc::gen::inRange(0, (int)arr.size());
    int j = *rc::gen::inRange(0, (int)arr.size());

    int val_i = arr[i];
    int val_j = arr[j];

    swap(&arr[i], &arr[j]);

    RC_ASSERT(arr[i] == val_j);
    RC_ASSERT(arr[j] == val_i);

    for (size_t k = 0; k < arr.size(); ++k) {
        if (k != (size_t)i && k != (size_t)j) {
            RC_ASSERT(arr[k] == values[k]);
        }
    }
}
