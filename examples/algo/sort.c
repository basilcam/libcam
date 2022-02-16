#include <cam/algo/sort.h>
#include <stdio.h>
#include <string.h>

void print_array(int *x, size_t length);

int main() {
    int x[] = {6, 6, 4, 2, 3, 5 ,1, 3, 8,9, 2, 3, 0, 0, 7};
    int num_elems = sizeof(x) / sizeof(int);
    print_array(x, num_elems);

    printf("sorting with quicksort, pivot moved to beginning\n");
    int temp[num_elems];
    memcpy(temp, x, sizeof(x));
    quicksorta(temp, sizeof(int), 0, num_elems - 1, cmp_int);
    print_array(temp, num_elems);

    printf("sorting with quicksort, pivot moved to end\n");
    memcpy(temp, x, sizeof(x));
    quicksortb(temp, sizeof(int), 0, num_elems - 1, cmp_int);
    print_array(temp, num_elems);

    printf("sorting with selectionsort\n");
    memcpy(temp, x, sizeof(x));
    selectionsort(temp, sizeof(int), num_elems, cmp_int);
    print_array(temp, num_elems);

    printf("sorting with bubblesort\n");
    memcpy(temp, x, sizeof(x));
    bubblesort(temp, sizeof(int), num_elems, cmp_int);
    print_array(temp, num_elems);

    printf("sorting with insertionsort\n");
    memcpy(temp, x, sizeof(x));
    insertionsort(temp, sizeof(int), num_elems, cmp_int);
    print_array(temp, num_elems);
}

void print_array(int *x, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");
}
