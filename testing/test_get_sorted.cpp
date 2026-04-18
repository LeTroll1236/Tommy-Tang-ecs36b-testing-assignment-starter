#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {1, 2, 3, 4, 5};
    int len = 5;

    int* sorted = get_sorted(ar, len);

    EXPECT_EQ(sorted[0], 1);
    EXPECT_EQ(sorted[1], 2);
    EXPECT_EQ(sorted[2], 3);
    EXPECT_EQ(sorted[3], 4);
    EXPECT_EQ(sorted[4], 5);

    free(sorted);
}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {9, 7, 5, 3, 1};
    int len = 5;

    int* sorted = get_sorted(ar, len);

    EXPECT_EQ(sorted[0], 1);
    EXPECT_EQ(sorted[1], 3);
    EXPECT_EQ(sorted[2], 5);
    EXPECT_EQ(sorted[3], 7);
    EXPECT_EQ(sorted[4], 9);

    free(sorted);
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {4, 1, 7, 2, 6};
    int len = 5;

    int* sorted = get_sorted(ar, len);

    EXPECT_EQ(sorted[0], 1);
    EXPECT_EQ(sorted[1], 2);
    EXPECT_EQ(sorted[2], 4);
    EXPECT_EQ(sorted[3], 6);
    EXPECT_EQ(sorted[4], 7);

    free(sorted);
}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {5, 2, 5, 1, 2};
    int len = 5;

    int* sorted = get_sorted(ar, len);

    EXPECT_EQ(sorted[0], 1);
    EXPECT_EQ(sorted[1], 2);
    EXPECT_EQ(sorted[2], 2);
    EXPECT_EQ(sorted[3], 5);
    EXPECT_EQ(sorted[4], 5);

    free(sorted);
}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {4, 1, 7, 2, 6};
    int original[] = {4, 1, 7, 2, 6};
    int len = 5;

    int* sorted = get_sorted(ar, len);

    for (int i = 0; i < len; i++) {
        EXPECT_EQ(ar[i], original[i]);
    }

    free(sorted);
}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {4, 1, 7, 2, 6};
    int len = 5;

    int* sorted = get_sorted(ar, len);

    EXPECT_NE(sorted, ar);
    EXPECT_EQ(sorted[0], 1);
    EXPECT_EQ(sorted[1], 2);
    EXPECT_EQ(sorted[2], 4);
    EXPECT_EQ(sorted[3], 6);
    EXPECT_EQ(sorted[4], 7);

    sorted[0] = 99;
    EXPECT_EQ(ar[0], 4);

    free(sorted);
}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    RC_PRE(!values.empty());

    int* ar = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) {
        ar[i] = values[i];
    }

    int* sorted = get_sorted(ar, values.size());

    for (size_t i = 0; i + 1 < values.size(); i++) {
        RC_ASSERT(sorted[i] <= sorted[i + 1]);
    }

    free(sorted);
    delete[] ar;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>& values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    ;
    RC_PRE(!values.empty());

    int* ar = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) {
        ar[i] = values[i];
    }

    int* sorted = get_sorted(ar, values.size());

    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(ar[i] == values[i]);
    }

    free(sorted);
    delete[] ar;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>& values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(!values.empty());

    int* ar = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) {
        ar[i] = values[i];
    }

    int* sorted = get_sorted(ar, values.size());

    RC_ASSERT(sorted != ar);

    for (size_t i = 0; i + 1 < values.size(); i++) {
        RC_ASSERT(sorted[i] <= sorted[i + 1]);
    }

    int original_first = ar[0];
    sorted[0] = sorted[0] + 1;
    RC_ASSERT(ar[0] == original_first);

    free(sorted);
    delete[] ar;
}











