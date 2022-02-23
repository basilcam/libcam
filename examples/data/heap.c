#include <stdio.h>
#include "cam/data/heap.h"

int int_cmp(const void *a, const void *b) {
    int *aint = (int *) a;
    int *bint = (int *) b;

    if (*aint < *bint) {
        return -1;
    } else if (*aint > *bint) {
        return 1;
    } else {
        return 0;
    }
}

static void print_heap(cam_heap *heap) {
    size_t size = cam_heap_get_size(heap);

    for (size_t index = 0; index < size; index++) {
        int *data = (int *) cam_heap_get_data(heap, index);
        printf("%d ", *data);
    }
    printf("\n");
}

static void insert(cam_heap *heap, int *data) {
    cam_heap_insert(heap, data);
    printf("inserting %d\n", *data);
    print_heap(heap);
}

static void remove_min(cam_heap *heap) {
    int *data = (int *) cam_heap_remove_min(heap);
    printf("removing min %d\n", *data);
    print_heap(heap);
}

int main() {
    int x1 = 2;
    int x2 = 6;
    int x3 = 4;
    int x4 = 1;

    cam_heap *heap = cam_heap_create(10, int_cmp);

    insert(heap, &x1);
    insert(heap, &x2);
    insert(heap, &x3);
    insert(heap, &x4);

    remove_min(heap);
    remove_min(heap);
    remove_min(heap);
    remove_min(heap);
}