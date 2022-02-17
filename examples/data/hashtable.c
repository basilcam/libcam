
#include <cam/data/hashtable.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


size_t hash(void *key) {
    size_t sum = 0;
    size_t p = 31;
    size_t pow = 1;
    for(char *c = (char *) key; *c != '\0'; c++) {
        sum += ((*c) - 'a' + 1) * pow;
        pow *= p;
    }
    return sum;
}

bool eq(void *a, void *b) {
    return strcmp((char *) a, (char *) b) == 0;
}

int main() {
    cam_ht *ht = cam_ht_create(hash, eq);

    const char *name1 = "cam";
    const int score1 = 12;
    cam_ht_put(ht, (void *) name1, (void *) &score1);
    printf("added (%s, %d) to map\n", name1, score1);

    const char *name2 = "mina";
    const int score2 = 50;
    cam_ht_put(ht, (void *) name2, (void *) &score2);
    printf("added (%s, %d) to map\n", name2, score2);

    void *raw = cam_ht_get(ht, (void *) name1);
    printf("resolved %s from map to %d\n", name1, *((int *) raw));

    raw = cam_ht_get(ht, (void *) name2);
    printf("resolved %s from map to %d\n", name2, *((int *) raw));

    const char *name3 = "pepita";
    raw = cam_ht_get(ht, (void *) name3);
    assert(raw == NULL);
    printf("resolved %s from map to NULL\n", name3);

    raw = cam_ht_remove(ht, (void *) name2);
    assert(raw != NULL);
    printf("removed %s from map, returned %d\n", name2, *((int *) raw));

    raw = cam_ht_get(ht, (void *) name2);
    assert(raw == NULL);
    printf("resolved %s from map to NULL\n", name2);

    exit(EXIT_SUCCESS);
}