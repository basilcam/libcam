#include <malloc.h>
#include <assert.h>
#include <stdbool.h>
#include "cam/data/linked_list.h"

cam_ll *cam_ll_init() {
    cam_ll *ll = (cam_ll *) malloc(sizeof(cam_ll));
    ll->start_node = NULL;
    ll->end_node = NULL;
    ll->size = 0;
    return ll;
}

void cam_ll_deinit(cam_ll *ll) {
    if (ll->size >= 0) {
        cam_ll_node *node = ll->start_node;
        while (node != NULL) {
            struct cam_ll_node_s *next_node = node->next_node;
            free(node);
            node = next_node;
        }
    }
}

size_t cam_ll_get_size(cam_ll *ll) {
    assert(ll != NULL);
    return ll->size;
}

bool cam_ll_is_empty(cam_ll *ll) {
    assert(ll != NULL);
    return ll->size == 0;
}

void cam_ll_add(cam_ll *ll, void *data) {
    assert(ll != NULL);

    cam_ll_node *node = (cam_ll_node *) malloc(sizeof(cam_ll_node));
    node->data = data;

    if (cam_ll_is_empty(ll)) {
        ll->start_node = node;
        ll->end_node = node;
        ll->size++;
        return;
    }

    ll->end_node->next_node = node;
    node->prev_node = ll->end_node;
    node->next_node = NULL;
    ll->end_node = node;
    ll->size++;
}

void cam_ll_add_at(cam_ll *ll, size_t index, void *data) {
    assert(ll != NULL);

    // append if index outside of list
    if (index >= ll->size) {
        cam_ll_add(ll, data);
        return;
    }

    // find node to evict
    cam_ll_node *node = ll->start_node;
    for (size_t i = 0; i < index; i++) {
        assert(node != NULL); // assertion valid given above size check
        node = node->next_node;
    }

    cam_ll_node *new_node = (cam_ll_node *) malloc(sizeof(cam_ll_node));
    new_node->data = data;
    new_node->prev_node = node->prev_node;
    new_node->next_node = node;

    if (node->prev_node != NULL) { // evicted node isn't start node
        node->prev_node->next_node = new_node;
    } else { // evicted node is start node
        ll->start_node = new_node;
    }
    node->prev_node = new_node;

    ll->size++;
}

void *cam_ll_remove(cam_ll *ll) {
    assert(ll != NULL);

    if (cam_ll_is_empty(ll)) {
        return NULL;
    }

    cam_ll_node *end_node = ll->end_node;

    cam_ll_node *new_end_node = end_node->prev_node;
    if (new_end_node != NULL) {
        new_end_node->next_node = NULL;
    }

    ll->end_node = new_end_node;
    ll->size--;

    void *data = end_node->data;
    free(end_node);
    return data;
}

void *cam_ll_remove_at(cam_ll *ll, size_t index) {
    assert(ll != NULL);

    // node with given index not in list
    if (index >= ll->size) {
        return NULL;
    }

    // find node to remove
    cam_ll_node *node = ll->start_node;
    for (size_t i = 0; i < index; i++) {
        assert(node != NULL); // assertion valid given above size check
        node = node->next_node;
    }

    // update previous node
    if (node->prev_node != NULL) { // removed node isn't start node
        node->prev_node->next_node = node->next_node;
    } else {
        ll->start_node = node->next_node;
    }

    // update next node
    if (node->next_node != NULL) { // removed node isn't end node
        node->next_node->prev_node = node->prev_node;
    } else {
        ll->end_node = node->prev_node;
    }

    ll->size--;

    void *data = node->data;
    free(node);
    return data;
}


///
/// iteration
///

// this should parallel listiterator
// todo: clarify functions that break when element removed

void cam_ll_iter_init(cam_ll *ll, cam_ll_iter *iter) {
    iter->ll = ll;
    iter->node = NULL;
    iter->index = -1;
    iter->next_node = ll->start_node;
}

size_t cam_ll_iter_get_index(cam_ll_iter *iter) {
    assert(iter != NULL);

    return iter->index;
}

bool cam_ll_iter_has_next(cam_ll_iter *iter) {
    assert(iter != NULL);

    return iter->next_node != NULL;
}

void *cam_ll_iter_next(cam_ll_iter *iter) {
    assert(iter != NULL);

    iter->node = iter->next_node;
    iter->prev_node = iter->node->prev_node;
    iter->next_node = iter->node->next_node;
    iter->index++;

    return iter->node->data;
}

bool cam_ll_iter_has_prev(cam_ll_iter *iter) {
    assert(iter != NULL);

    return iter->prev_node != NULL;
}

void *cam_ll_iter_prev(cam_ll_iter *iter) {
    assert(iter != NULL);

    iter->node = iter->prev_node;
    iter->prev_node = iter->node->prev_node;
    iter->next_node = iter->node->next_node;
    iter->index--;

    return iter->node->data;
}

void *cam_ll_iter_remove(cam_ll_iter *iter) {
    assert(iter != NULL && iter->node != NULL);

    cam_ll_node *next_node = iter->node->next_node;
    cam_ll_node *prev_node = iter->node->prev_node;

    if (next_node != NULL) {
        next_node->prev_node = iter->prev_node;
    }

    if (prev_node != NULL) {
        prev_node->next_node = iter->next_node;
    }

    void *data = iter->node->data;
    free(iter->node);
    iter->node = NULL;
    iter->index--;
    return data;
}

void cam_ll_iter_add(cam_ll_iter *iter, void *data) {
    assert(iter != NULL);

    cam_ll_node *new_node = (cam_ll_node *) malloc(sizeof(cam_ll_node));
    new_node->data = data;
    new_node->prev_node = iter->prev_node;
    new_node->next_node = iter->next_node;

    iter->node->prev_node = new_node;
    iter->prev_node = new_node;

    iter->ll->size++;
}





