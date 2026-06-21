#include <stdlib.h>
#define MAX_ITEMS 50000

int
removeDuplicates(int *nums, int numsSize)
{
    if (numsSize == 0)
        return 0;

    int unique_nums_size = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[unique_nums_size]) {
            nums[unique_nums_size++] = nums[i];
        }
    }

    return unique_nums_size;
}

int
main()
{
    return 0;
}
