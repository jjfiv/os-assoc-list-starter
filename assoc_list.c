#include "assoc_list.h"
#include <stdlib.h> // malloc, free

// Construct a new association list (completed).
AssocList_t* assoc_new(void) {
	AssocList_t* self = malloc(sizeof(AssocList_t));
	assert(self != NULL);
	self->num_elements = 0;
	self->head = NULL;
	return self;
}

// Put a (key, value) pair into this list, overriding previous versions of the key if applicable.
void assoc_put(AssocList_t* self, bytes_t* key, bytes_t* value) {
	assert(self != NULL);
	assert(key != NULL);
	assert(value != NULL);

	printf("called assoc_put: ");
        bytes_print(stdout, key);
        printf(" ");
        bytes_print(stdout, value);
        printf("\n");
	
	// if the list is empty, create a new head entry
	if (self->head == NULL) {
	  AssocEntry_t* new_head = malloc(sizeof(AssocEntry_t));
          new_head->key = key;
          new_head->value = value;
          new_head->next = NULL;
	  self->head = new_head;
	  return;
	}

	// if the key already exists in the list, override the old entry
	AssocEntry_t* curr = self->head;
	while (curr != NULL) {
	  if (bytes_equal(curr->key, key)) {
	    curr->value = value;
	    return;
	  }
	  curr = curr->next;
	}

	// otherwise, create a new entry and add it to the head of the list
	AssocEntry_t* entry = malloc(sizeof(AssocEntry_t));
        entry->key = key;
        entry->value = value;
        entry->next = NULL;
	AssocEntry_t* old_head = self->head;
	entry->next = old_head;
	self->head = entry;
	
	self->num_elements += 1;
}

// Remove an entry matching this key in the association list.
void assoc_remove(AssocList_t* self, bytes_t* key) {
	assert(self != NULL);
	assert(key != NULL);

	// traverse the list while keeping track of the matching entry and the entry before it
	AssocEntry_t* curr = self->head;
	AssocEntry_t* prev = NULL;
	while (curr != NULL && !bytes_equal(curr->key, key)) {
	  prev = curr;
	  curr = curr->next;
	  if (curr == NULL) printf("%s", "the key doesn't exist");
	}

	// if the head entry has the matching key, update the head entry
	if (prev == NULL) {
	  self->head = curr->next;
	  free(curr);

	// otherwise update the matching entry
	} else {
	  prev->next = curr->next;
	  free(curr);
	}

	self->num_elements -= 1;
	
	printf("called assoc_remove: ");
	bytes_println(stdout, key);
}

// Lookup an entry matching this key and return a pointer to its value.
bytes_t* assoc_get(AssocList_t* self, bytes_t* key) {
	assert(self != NULL);
	assert(key != NULL);

	printf("called assoc_get: ");
	bytes_println(stdout, key);

	// TODO: finish this method; return NULL if missing!
	AssocEntry_t* curr = self->head;
	while (curr != NULL) {
	  if (bytes_equal(curr->key, key)) {
	    return curr->value;
	  }
	  curr = curr->next;
	}
	return NULL;
}

// Remove all entries from this list (try to free in the right places!)
void assoc_clear(AssocList_t* self) {
	assert(self != NULL);

	AssocEntry_t* current = self->head;
	AssocEntry_t* next = NULL;
	while(current != NULL) {
		// grab next:
		next = current->next;
		// delete current:
		bytes_free(current->key);
		bytes_free(current->value);
		free(current);
		// move to next
		current = next;
	}

	// Finish clearing data:
	self->num_elements = 0;
	self->head = NULL;
}

// Lookup the number of elements in this data structure; prefer O(1) to O(n).
size_t assoc_size(AssocList_t* self) {
	assert(self != NULL);
	return self->num_elements;
}
