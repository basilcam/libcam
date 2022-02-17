#ifndef LIBCAM_HASHTABLE_H
#define LIBCAM_HASHTABLE_H

#include <stddef.h>
#include <stdbool.h>

struct cam_ht_s;
typedef struct cam_ht_s cam_ht;

typedef size_t (*cam_ht_hash)(void *key);
typedef bool (*cam_ht_eq)(void *key1, void *key2);

cam_ht *cam_ht_create(cam_ht_hash hash, cam_ht_eq eq);
void *cam_ht_get(cam_ht *ht, void *key);
void cam_ht_put(cam_ht *ht, void *key, void *value);
void *cam_ht_remove(cam_ht *ht, void *key);

#endif //LIBCAM_HASHTABLE_H
