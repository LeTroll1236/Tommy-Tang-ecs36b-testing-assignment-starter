#include <stdlib.h>
#include "sorting.h"
#include <stdlib.h>

int* get_sorted(int* ar, int len) {
  /**
 * Return a COPY of ar in sorted order.
 * @param ar: The array to make a sorted copy of.
 * @param len: The length of ar
 * @return: A sorted copy of
 */

  int* sorted_ar = copy_array(ar, len);
  make_sorted(sorted_ar, len);
  return sorted_ar;
}

void make_sorted(int* ar, int len) {
  /**
 * Sort the given array in place.
 * @param ar: The array to be sorted.
 * @param len: The length of the array to be sorted.
 */
  for (int i = 0; i < len; ++i) {
    int min_index = min_index_of_array(ar + i, len - i);
    swap(ar + i, ar + i + min_index);
  }
}

int* copy_array(int* ar, int len) {
  /**
  * Return a copy of the array
  * @param ar: The array to copy
  * @param len: The length of the array to copy
  * @return: A copy of ar
  */
  int* copy = (int*) malloc(len * sizeof(int));

  for (int i = 0; i < len; i++) {
    copy[i] = ar[i];
  }

  return copy;
}

int min_index_of_array(int* ar, int len) {
  /**
 * Find the INDEX of the minimum value in ar. If there are multiple values that are
 * the minimum, return the index of the first minimum.
 * @param ar: The array to search through
 * @param len: the number of elements in ar
 * @return: The INDEX of the minimum value in ar
 */

  int min_index = 0;

  for (int i = 1; i < len; ++i) {
    if (ar[i] < ar[min_index]) {
      min_index = i;
    }
  }

  return min_index;
}

void swap(int* a, int* b) {
  /**
 * Swap the values held in a and b.
 * @param a: The address of the first element to swap.
 * @param b: The address of the second element to swap.
 */

  int temp = *a;
  *a = *b;
  *b = temp;
}
