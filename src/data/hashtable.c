#include <stddef.h>
#include <malloc.h>
#include <assert.h>
#include "cam/data/hashtable.h"

struct ht_node_s {
    void *key;
    void *value;
    struct ht_node_s *next;
};
typedef struct ht_node_s ht_node;

struct cam_ht_s {
    cam_ht_hash hash;
    cam_ht_eq eq;
    ht_node *buckets;
    size_t num_buckets;
    size_t size;
};

static const size_t START_NUM_BUCKETS = 32;

static size_t calc_bucket_index(cam_ht *ht, void *key);
static void rehash(cam_ht *ht);
static void put(cam_ht *ht, void *key, void *value);

cam_ht *cam_ht_create(cam_ht_hash hash, cam_ht_eq eq) {
    assert(hash != NULL && eq != NULL);

    cam_ht *ht = (cam_ht *) malloc(sizeof(cam_ht));
    ht->hash = hash;
    ht->eq = eq;
    ht->num_buckets = START_NUM_BUCKETS;
    ht->buckets = (ht_node *) malloc(sizeof(ht_node) * ht->num_buckets);
    ht->size = 0;

    // todo: could also make this an array of pointers, and initialize each to NULL
    for (size_t i = 0; i < ht->num_buckets; i++) {
        ht->buckets[i].key = NULL;
        ht->buckets[i].value = NULL;
        ht->buckets[i].next = NULL;
    }

    return ht;
}

void *cam_ht_get(cam_ht *ht, void *key) {
    assert(ht != NULL && key != NULL);

    size_t bucket_idx = calc_bucket_index(ht, key);

    ht_node *bucket = ht->buckets + bucket_idx;
    for (ht_node *node = bucket; node != NULL; node = node->next) {
        if (node->key != NULL && ht->eq(key, node->key)) {
            return node->value;
        }
    }
    return NULL;
}

void cam_ht_put(cam_ht *ht, void *key, void *value) {
    assert(ht != NULL && key != NULL && value != NULL);

    rehash(ht);
    put(ht, key, value);
}

void *cam_ht_remove(cam_ht *ht, void *key) {
    assert(ht != NULL && key != NULL);

    size_t bucket_idx = calc_bucket_index(ht, key);
    if (ht->buckets[bucket_idx].key == NULL) {
        return NULL;
    }


    ht_node *node = &ht->buckets[bucket_idx];
    if (ht->eq(node->key, key)) {
        node->key = NULL;
        void *value = node->value;

        // copy next node into bucket, free it
        ht_node *next = node->next;
        if (next != NULL) {
            node->key = next->key;
            node->value = next->value;
            node->next = next->next;
            free(next);
        }
        ht->size--;
        return value;
    }

    ht_node *last = node;
    node = node->next;
    while (node != NULL) {
        if (ht->eq(key, node->key)) {
            last->next = node->next;
            void *data = node->value;
            free(node);
            ht->size--;
            return data;
        }

        last = node;
        node = node->next;
    }
    return NULL;
}

static size_t calc_bucket_index(cam_ht *ht, void *key) {
    assert(ht != NULL);

    return ht->hash(key) % ht->num_buckets;
}

static void rehash(cam_ht *ht) {
    assert(ht != NULL);

    if (ht->size < (size_t)(ht->num_buckets * 0.75)) {
        return;
    }

     size_t old_num_buckets = ht->num_buckets;
     ht_node *old_buckets = ht->buckets;

     ht->num_buckets <<= 1;
     ht->buckets = (ht_node *) malloc(sizeof(ht_node) * ht->num_buckets);

     for (size_t i = 0; i < old_num_buckets; i++) {
         if (old_buckets[i].key == NULL) { // completely empty
             continue;
         }

         put(ht, old_buckets[i].key, old_buckets[i].value);

         ht_node *node = old_buckets[i].next;
         while (node != NULL) {
             put(ht, node->key, node->value);

             ht_node *next = node->next;
             free(node);
             node = next;
         }
     }
}

static void put(cam_ht *ht, void *key, void *value) {
    size_t bucket_idx = calc_bucket_index(ht, key);
    ht_node *bucket = ht->buckets + bucket_idx;

    if (bucket->key == NULL) {
        bucket->key = key;
        bucket->value = value;
        ht->size++;
        return;
    }

    ht_node *last = bucket;
    ht_node *node = bucket;
    while (node != NULL) {
        if (ht->eq(node->key, key)) {
            node->value = value;
            return;
        }
        last = node;
        node = node->next;
    }

    node = (ht_node *) malloc(sizeof(ht_node));
    node->key = key;
    node->value = value;
    node->next = NULL;
    last->next = node;
}
