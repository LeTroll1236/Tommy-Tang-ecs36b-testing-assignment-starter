#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {1, 2, 3, 4};
    int len = 4;

    int* copy = copy_array(ar, len);

    for (int i = 0; i < len; i++) {
        EXPECT_EQ(copy[i], ar[i]);
    }

    free(copy);
}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {1, 2, 3, 4, 5};
    int len = 5;
    int original[] = {1, 2, 3, 4, 5};

    int* copy = copy_array(ar, len);
    copy[0] = 99;

    for (int i = 0; i < len; i++) {
        EXPECT_EQ(ar[i], original[i]);
    }

    free(copy);
}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int ar[] = {1, 2, 3, 4, 5, 6};
    int len = 6;

    int* copy = copy_array(ar, len);

    EXPECT_NE(copy, ar);

    for (int i = 0; i < len; i++) {
        EXPECT_EQ(copy[i], ar[i]);
    }

    copy[0] = 99;
    EXPECT_NE(copy[0], ar[0]);

    free(copy);
}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(!values.empty());

    int* ar = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) {
        ar[i] = values[i];
    }

    int* copy = copy_array(ar, values.size());

    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(copy[i] == ar[i]);
    }

    free(copy);
    delete[] ar;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>& values)
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE(!values.empty());

    int* ar = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) {
        ar[i] = values[i];
    }

    int* copy = copy_array(ar, values.size());

    if (!values.empty()) {
        copy[0] = copy[0] + 1;
    }

    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(ar[i] == values[i]);
    }

    free(copy);
    delete[] ar;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>& values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */
    RC_PRE(!values.empty());

    int* ar = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) {
        ar[i] = values[i];
    }

    int* copy = copy_array(ar, values.size());

    RC_ASSERT(copy != ar);

    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(copy[i] == ar[i]);
    }

    copy[0] = copy[0] + 1;
    RC_ASSERT(ar[0] == values[0]);

    free(copy);
    delete[] ar;
}



