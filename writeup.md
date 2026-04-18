# Google Test And Debugging Writeup

## Things I Thought To Test
1. Check for improper syntax
2. Test each function individually to check if they behave as intended
   1. swap: make sure the VALUES are being swapped correctly
   2. copy_array: just make sure that the int array is being copied and is a value at a different location
   3. min_index_of_array: make sure the function returns the INDEX, and the min VALUE of the array is being found - also test for multiple same min values and check if first min value's index is returned
   4. make_sorted: check if the array is sorted after the function ran
   5. get_sorted: check if a new copy of the sorted array is made at a different location
   6. parse_args: check if there are no command line arguments the out variable should be set to NULL


## Bugs

### Bug 1

### Location

Lines 37 - 38 in sorting.c

```c++
  int* copy = ar;
  return copy;
```

### How the bug was located

the original function didn't use the parameter len, and I suspected that this function didn't make a new memory space for the same array.

### Description

This just makes the array copy point to the same memory as the array ar

### Fix 

I made the array copy dynamically allocated at a new memory spot and copied each item from the original array

```c++
  int* copy = (int*) malloc(len * sizeof(int));

  for (int i = 0; i < len; i++) {
    copy[i] = ar[i];
  }

  return copy;
```

### Bug 2

### Location

Line 22 - 39 in formating.c

```c++
void parse_args(int argc, char** argv, int* ar_out, int* len_out){
  /**
 * Transform the command line arguments from their string representations to their numeric values
 * @param argc: the number of the command line arguments
 * @param argv: the command line arguments
 * @param ar_out: An output parameter. The array to store the command line arguments into. It is assumed that
   * no space has been made for the values so this function will allocate the space for the values inside of ar_out.
   * If there are no command line arguments ar_out should be set to NULL.
 * @param len_out:  An output parameter. The number of elements placed into ar_out.
 */

  *len_out = argc - 1;
  ar_out = (int*)malloc(*len_out);
  for(int i = 0; i < *len_out; ++i){
    sscanf(argv[i], "%d", ar_out[i]);
  }

}
```

### How the bug was located

I was reading the assumed condition that the ar_out must be allocated within this function, but figured the parameter of only int* does not fit this function.

### Description

The parameter of int* for ar_out will not suffice for a dynamically allocated array created inside the function, and allocation size was wrong with a wrong argv indexing. Also, there was no condition to check for empty command line argument.

### Fix

Changed int* for ar_out to be int** for it to be allocated in the function, added condition for empty command line argument, adjusted the allocation size, and changed the argv indexing

```c++
void parse_args(int argc, char** argv, int** ar_out, int* len_out) {
  /**
 * Transform the command line arguments from their string representations to their numeric values
 * @param argc: the number of the command line arguments
 * @param argv: the command line arguments
 * @param ar_out: An output parameter. The array to store the command line arguments into. It is assumed that
   * no space has been made for the values so this function will allocate the space for the values inside of ar_out.
   * If there are no command line arguments ar_out should be set to NULL.
 * @param len_out:  An output parameter. The number of elements placed into ar_out.
 */
  *len_out = argc - 1;

  if (*len_out == 0) {
    *ar_out = NULL;
    return;
  }

  *ar_out = (int*)malloc((*len_out) * sizeof(int));

  for (int i = 0; i < *len_out; ++i) {
    sscanf(argv[i + 1], "%d", &((*ar_out)[i]));
  }
}

```

### Bug 3

### Location

Lines 14 - 16 in main.c

```c++
  int* given_numbers;
  int len;
  parse_args(argc, argv, given_numbers, &len);
```

### How the bug was located

Since I changed the parse_args function to take a int** instead of a int* to fix the allocation problem, we have to change the input for the function when it is used.

### Description

Incorrect parameters for the function.

### Fix

Corrected the argument for the parameter parse_args, and added free to the end to free the allocation space.

```c++
int main(int argc, char* argv[]){

  int* given_numbers = NULL;
  int len = 0;

  parse_args(argc, argv, &given_numbers, &len);
  int* sorted_ar = get_sorted(given_numbers, len);

  printf("The numbers you entered are: ");
  print_ar(given_numbers, len);
  printf("\n");

  printf("After sorting the numbers we have: ");
  print_ar(sorted_ar, len);
  printf("\n");

  free(given_numbers);
  free(sorted_ar);

  return 0;
}
```

### Bug 4

### Location

Lines 72-74 of sorting.c

```c++
  int* temp = a;
  a = b;
  b = temp;
```

### How the bug was located

Ran test_swap.cpp

### Description

The returned values are not swapped, and all the tests are failed.

### Fix

Looked at the function swap, and saw that it was not swapping the values stored at the addresses.

```c++
  int temp = *a;
  *a = *b;
  *b = temp;
```

### Bug 5

### Location

Lines 55 - 62 in sorting.c

```c++
  int min_index = 0;

  for (int i = 1; i < len; ++i) {
    if (ar[i] > ar[min_index]) {
      min_index = i;
    }
  }
  return ar[min_index];
```

### How the bug was located

Running tests on test_min_index_of_array.cpp

### Description

The current outputs are numbers that are obviously out of range of the arrays ie. getting an output of 9 when the highest index was 3.

### Fix

Found that the comparison was finding the maximum, not the minimum. Also found that it was returning the value of the found, not the index of it.

```c++
  int min_index = 0;

  for (int i = 1; i < len; ++i) {
    if (ar[i] < ar[min_index]) {
      min_index = i;
    }
  }

  return min_index;
```

### Bug 6

### Location

Lines 24-27 in sorting.c

```c++
  for (int i = 0; i < len; ++i) {
    int min_index = min_index_of_array(ar + i, len);
    swap(ar + i, ar + min_index);
  }
```

### How the bug was located

Ran test_make_sorted.cpp

### Description

All the failed tests show that the array was not changed whatsoever, so 1st test case passed, and all other test cases were all unchanged and didn't pass.

### Fix

The usage of the function min_index_of_array was incorrect in the function, during the loop ar + i was being checked, but the length of the array being checked was changing, so in the int len parameter needed to be len - i to adjust the length with the loop. Also change the actual address from ar + min_index to ar + i + min_index.

```c++
  for (int i = 0; i < len; ++i) {
    int min_index = min_index_of_array(ar + i, len - i);
    swap(ar + i, ar + i + min_index);
  }
```

### Bug 7

### Location

lines 13-15 in sorting.c

```c++
  int* sorted_ar = copy_array(ar, len);
  make_sorted(ar, len);
  return sorted_ar;
```

### How the bug was located

Ran test_get_sorted.cpp

### Description

The resulting failed tests all showed that the output was the orignal unsorted array.

### Fix

The usage of make_sorted was correct, but the inputted array that needed to be sorted was not the right array. Was origninally just sorting the given parameter array and not the new copy.

```c++
  int* sorted_ar = copy_array(ar, len);
  make_sorted(sorted_ar, len);
  return sorted_ar;
```

### Bug 8

### Location

lines 17-19 in formatting.c

```c++
  for(int i = 0; i < len; --i){
    printf("%d ", ar[i]);
  }
```

### How the bug was located

Trying to run the whole main.c and was not getting output.

### Description

No print output from this function when the inputs are given and processed. This was because of an infinite loop error in the for loop.

### Fix

change --i to ++i, as we are not decreasing, we are increasing until we hit i < len, and finally being able to print out our solution.

```c++
  for(int i = 0; i < len; ++i){
    printf("%d ", ar[i]);
  }
```