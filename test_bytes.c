#include "bytes.h"
#include <assert.h>

int main(int argc, char **argv) {
	bytes_t* foo = bytes_new_empty();
	bytes_push(foo, 'x');
	bytes_push(foo, 'y');
	assert(bytes_eq(foo, "xy"));
	for (int i=0; i<9; i++) {
		bytes_push(foo, 'a'+i);
	}
	assert(bytes_eq(foo, "xyabcdefghi"));
	bytes_debug(foo);
	
	// delete bytes and debug again:
	bytes_clear(foo);
	bytes_debug(foo);

	bytes_t* wasted_space = bytes_copy_str("\tindented and extra \n");
	bytes_debug(wasted_space);
	
	bytes_trim(wasted_space);
	bytes_debug(wasted_space);
	assert(bytes_eq(wasted_space, "indented and extra"));
}
