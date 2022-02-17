#include <stdio.h>
#include <stdlib.h>
#include <cam/data/linked_list.h>

void print_list(cam_ll *ll) {
    cam_ll_iter iter;
    cam_ll_iter_init(ll, &iter);
    printf("\n\nprinting linked list...\n");
    while(cam_ll_iter_has_next(&iter)) {
        long *data = (long *) cam_ll_iter_next(&iter);

        size_t index = cam_ll_iter_get_index(&iter);
        printf("data at index %zu: %ld\n", index, *data);
    }
    printf("stop! reverse...\n");
    while(cam_ll_iter_has_prev(&iter)) {
        long *data = (long *) cam_ll_iter_prev(&iter);

        size_t index = cam_ll_iter_get_index(&iter);
        printf("data at index %zu, %ld\n", index, *data);
    }
    printf("\n\n");
}

int main() {
    long data1 = 1;
    long data2 = 2;
    long data3 = 3;

    cam_ll *ll = cam_ll_create();
    cam_ll_add(ll, &data1);
    cam_ll_add_at(ll, 0, &data2);
    cam_ll_add(ll, &data3);

    print_list(ll);

    long *data = cam_ll_remove_at(ll, 0);
    printf("removed %ld at index 0\n", *data);

    data = cam_ll_remove_at(ll, 1);
    printf("removed %ld at index 1\n", *data);

    cam_ll_add_at(ll, 0, &data3);
    printf("added %ld at index 0\n", data3);

    cam_ll_add_at(ll, 2, &data2);
    printf("added %ld at index 2\n", data2);

    print_list(ll);

    cam_ll_destroy(ll);

    exit(EXIT_SUCCESS);
}

