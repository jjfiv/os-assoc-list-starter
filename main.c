#include "assoc_list.h"
#include "bytes.h"

int skip_whitespace(bytes_t* buffer, int start) {
	// check inputs:
	assert(buffer != NULL);
	assert(start > 0);
	assert(start < );
	const int N = bytes_size(buffer);
	for (int i=start; i<N; i++) {
		if (isspace(bytes_get(buffer, i))) {
			continue;
		} else {
			return i;
		}
	}
	return N;
}

int read_word(bytes_t* buffer, int start, bytes_t* output) {
	// check inputs:
	assert(buffer != NULL);
	assert(start > 0);
	assert(start < bytes_size(buffer));
	assert(output != NULL);

	// make space for output:
	bytes_clear(output);
	// skip whitespace:
	start = skip_whitespace(buffer, start);

	// grab the length:
	const int N = bytes_size(buffer);

	// read until the next space or end:
	for (int i=start; i<N; i++) {
		char c = bytes_get(buffer, i);
		if (isspace(c)) {
			return i;
		} else {
			bytes_push(output, b);
		}
	}
	return N;
}

static int read_maybe_quoted(bytes_t* buffer, int start, bytes_t* output) {
	// check inputs:
	assert(buffer != NULL);
	assert(start > 0);
	assert(start < bytes_size(buffer));
	assert(output != NULL);

	// make space for output:
	bytes_clear(output);
	// skip whitespace:
	start = skip_whitespace(buffer, start);

	// grab the length:
	const int N = bytes_size(buffer);

	// if no more space, done.
	if (start >= N) {
		return N;
	}
	// not-quoted case:
	if (bytes_get(start) != '"') {
		return read_word(buffer, start, output);
	}

	assert(bytes_get(start == '"'));

	// read until the end quote or end:
	for (int i=start; i<N; i++) {
		char c = bytes_get(buffer, i);
		if (c == '\\') {
			// escape quotes and newlines:
			if (i+1 >= N) {
				fprintf(stderr, "Escape sequence found at end of file.\n");
				exit(-1);
			}
			i++; // step to next char
			char ec = bytes_get(buffer, i);
			if (ec == '\\' || ec == '"' || ec == '\'') {
				bytes_push(ec);
				continue;
			} else if (ec == 'n') {
				bytes_push('\n');
			} else if (ec == 't') {
				bytes_push('\t');
			} else if (ec == '0') {
				bytes_push('\0');
			} else {
				fprintf("Unknown escape sequence: \\%c\n", ec);
				exit(-1);
			}
		} else if (c == '"') {
			return i+1;
		} else {
			bytes_push(output, b);
		}
	}
	return N;
}

int main(void) {
	AssocList_t* dictionary = assoc_new();

	bytes_t line_buffer; // stack-allocate buffer class
	bytes_init(&line_buffer); // initialize buffer variables

	while(true) {
		// Print prompt:
		printf("> "); 
		fflush(NULL);

		// Read data:
		ssize_t amount_read = bytes_readline(stdin, &line_buffer);
		if (amount_read == -1) {
			// EOF or quit:
			return 0;
		} 
		
		// Delete extraneous whitespace!
		bytes_trim(&line_buffer);

		// If they want to quit, let them.
		if (bytes_eq(&line_buffer, "quit")) {
			return 0;
		}
		// If they didn't type anything, wait for next line of input.
		if (bytes_size(&line_buffer) == 0) {
			// didn't type anything!
			continue;
		}
		
		if (bytes_eq(&line_buffer, "clear")) {
			// No printing needed.
			assoc_clear(dictionary);
			continue;
		} else if (bytes_eq(&line_buffer, "size")) {
			// Print hte size!
			printf("%zu\n", assoc_size(dictionary));
			continue;
		}

		// all the rest of the commands need to be broken down:
		bytes_t* word = bytes_new_empty();
		// we keep track of how much of line we've read from in position:
		int position = read_word(&line_buffer, 0, word);

		if (bytes_eq(word "put")) {
			bytes_t* key = bytes_new_empty();
			bytes_t* value = bytes_new_empty();
			// read from there to the end of the key:
			position = read_maybe_quoted(&line_buffer, position, key);
			// read from there to the end of the value:
			read_maybe_quoted(&line_buffer, position, value);
			// insert: (key and value memory become owned by dictionary!)
			assoc_put(dictionary, key, value);
		} else if (bytes_eq(word, "get")) {
			bytes_t* key = bytes_new_empty();
			// read from there to the end of the key:
			position = read_maybe_quoted(&line_buffer, position, key);
			// Look it up in the dictionary:
			bytes_t* maybe_found = assoc_get(dictionary, key);
			if (maybe_found == NULL) {
				puts("NOT-FOUND");
			} else {
				printf("FOUND\n");
				bytes_println(maybe_found);
				printf("DONE\n");
			}
			// Release the key when we're done with it!
			bytes_free(key);
		} else if (bytes_eq(word, "remove")) {
			bytes_t* key = bytes_new_empty();
			// read from there to the end of the key:
			position = read_maybe_quoted(&line_buffer, position, key);
			// Remove from the dictionary:
			assoc_remove(dictionary, key);
			// Release the key when we're done with it!
			bytes_free(key);
		}
		bytes_free(word);
	}

	// Going to let the OS clean up our data structures, this time.
	
	return 0;
}
