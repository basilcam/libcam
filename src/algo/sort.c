#include <string.h>
#include <stdint-gcc.h>
#include <sys/types.h>
#include "cam/algo/sort.h"

static void swap(void *a, void *b, size_t size);

int cmp_int(void *a, void *b) {
    int *a1 = (int *) a;
    int *b1 = (int *) b;

    if (*a1 > *b1) {
        return 1;
    } else if (*a1 < *b1) {
        return -1;
    } else {
        return 0;
    }
}

void quicksorta(void *array, size_t elem_size, size_t left_idx, size_t right_idx, cam_cmp comparator) {
    if (left_idx >= right_idx) {
        return;
    }

    void *left_ptr = array + left_idx * elem_size;

    // find pivot
    size_t mid_idx = (left_idx + right_idx) / 2;
    void *mid_ptr = array + mid_idx * elem_size;

    // move pivot to beginning of array
    swap(left_ptr, mid_ptr, elem_size);

    size_t last_idx = left_idx;
    for (size_t i = left_idx + 1; i <= right_idx; i++) {
        void *curr_ptr = array + i * elem_size;

        // compare current element against pivot, swap with last larger
        if ((*comparator)(curr_ptr, left_ptr) <= 0) {
            last_idx++;
            void *last_ptr = array + last_idx * elem_size;
            swap(curr_ptr, last_ptr, elem_size);
        }
    }

    // swap pivot from beginning of array to last element smaller than pivot
    void *last_ptr = array + last_idx * elem_size;
    swap(left_ptr, last_ptr, elem_size);

    if (last_idx != 0) {
        quicksorta(array, elem_size, left_idx, last_idx - 1, comparator);
    }
    quicksorta(array, elem_size, last_idx + 1, right_idx, comparator);
}

void quicksortb(void *array, size_t elem_size, size_t left_idx, size_t right_idx, cam_cmp comparator) {
    if (left_idx >= right_idx) {
        return;
    }

    void *right_ptr = array + right_idx * elem_size;

    // find pivot
    size_t mid_idx = (left_idx + right_idx) / 2;
    void *mid_ptr = array + mid_idx * elem_size;

    // move pivot to end of array
    swap(right_ptr, mid_ptr, elem_size);

    size_t last_idx = left_idx;
    for (size_t i = left_idx; i <= right_idx - 1; i++) {
        void *curr_ptr = array + i * elem_size;

        // compare current element against pivot
        // if current element <= pivot, swap it with last element >= pivot
        if ((*comparator)(curr_ptr, right_ptr) <= 0) {
            void *last_ptr = array + last_idx * elem_size;
            swap(curr_ptr, last_ptr, elem_size);
            last_idx++;
        }
    }

    // swap pivot from end of array to last element greater than pivot
    void *last_ptr = array + last_idx * elem_size;
    swap(right_ptr, last_ptr, elem_size);

    if (last_idx != 0) {
        quicksortb(array, elem_size, left_idx, last_idx - 1, comparator);
    }
    quicksortb(array, elem_size, last_idx + 1, right_idx, comparator);
}

void selectionsort(void *array, size_t elem_size, size_t length, cam_cmp comparator) {
    for (size_t i = 0; i < length - 1; i++) {
        void *i_ptr = array + i * elem_size;

        void *min_ptr = i_ptr;
        for (size_t j = i + 1; j < length; j++) {
            void *j_ptr = array + j * elem_size;
            if ((*comparator)(j_ptr, min_ptr) < 0) {
                min_ptr = j_ptr;
            }
        }

        swap(min_ptr, i_ptr, elem_size);
    }
}

void bubblesort(void *array, size_t elem_size, size_t length, cam_cmp comparator) {
    for (size_t i = 0; i < length - 1; i++) {
        for (size_t j = 0; j < length - i - 1; j++) {
            void *a = array + j * elem_size;
            void *b = array + (j + 1) * elem_size;
            if ((*comparator)(a, b) > 0) {
                swap(a, b, elem_size);
            }
        }
    }
}

void insertionsort(void *array, size_t elem_size, size_t length, cam_cmp comparator) {
    for (ssize_t i = 1; i < length; i++) {
        char key[elem_size];
        memcpy(key, array + i * elem_size, elem_size);

        size_t j = 0;
        while (j <= i - 1 && (*comparator)(array + (i - 1 - j) * elem_size, key) > 0) {
            memcpy(array + (i - j) * elem_size, array + (i - 1 - j) * elem_size, elem_size);
            j++;
        }

        // copy key into last position that was copied from
        memcpy(array + (i - j) * elem_size, &key, elem_size);
    }
}

// todo: add mergesort

static void swap(void *a, void *b, size_t size) {
    uint8_t temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}
