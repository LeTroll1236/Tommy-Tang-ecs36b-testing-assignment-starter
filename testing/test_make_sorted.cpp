#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {1, 2, 3, 4, 5};
    int len = 5;

    make_sorted(ar, len);

    EXPECT_EQ(ar[0], 1);
    EXPECT_EQ(ar[1], 2);
    EXPECT_EQ(ar[2], 3);
    EXPECT_EQ(ar[3], 4);
    EXPECT_EQ(ar[4], 5);
}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {9, 7, 5, 3, 1};
    int len = 5;

    make_sorted(ar, len);

    EXPECT_EQ(ar[0], 1);
    EXPECT_EQ(ar[1], 3);
    EXPECT_EQ(ar[2], 5);
    EXPECT_EQ(ar[3], 7);
    EXPECT_EQ(ar[4], 9);
}


TEST(MakeSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {4, 1, 7, 2, 6};
    int len = 5;

    make_sorted(ar, len);

    EXPECT_EQ(ar[0], 1);
    EXPECT_EQ(ar[1], 2);
    EXPECT_EQ(ar[2], 4);
    EXPECT_EQ(ar[3], 6);
    EXPECT_EQ(ar[4], 7);
}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {5, 2, 5, 1, 2};
    int len = 5;

    make_sorted(ar, len);

    EXPECT_EQ(ar[0], 1);
    EXPECT_EQ(ar[1], 2);
    EXPECT_EQ(ar[2], 2);
    EXPECT_EQ(ar[3], 5);
    EXPECT_EQ(ar[4], 5);
}

RC_GTEST_PROP(MakeSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Test that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(!values.empty());

    int* ar = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) {
        ar[i] = values[i];
    }

    make_sorted(ar, values.size());

    for (size_t i = 0; i + 1 < values.size(); i++) {
        RC_ASSERT(ar[i] <= ar[i + 1]);
    }

    delete[] ar;
}
