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

	// TODO: finish this method.
	printf("called assoc_put: ");
	bytes_print(stdout, key);
	printf(" ");
	bytes_print(stdout, value);
	printf("\n");
}

// Remove an entry matching this key in the association list.
void assoc_remove(AssocList_t* self, bytes_t* key) {
	assert(self != NULL);
	assert(key != NULL);

	// TODO: finish this method.
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
