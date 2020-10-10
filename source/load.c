#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>

#include "load.h"

uint8_t *load_file(char *file_name) {

	FILE *f;
	struct stat st;
	uint8_t *code;

	code = NULL;

	if (f = fopen(file_name, "r")) {

		fstat(fileno(f), &st); // fileno() returns the file descriptor number // gets status information about the file specified by the open file descriptor and stores it

		if (st.st_size) {

			code = malloc(st.st_size); // allocate space for the array
			fread(code, sizeof(*code), st.st_size, f); // reads data from the stream into the array pointed to, by pointer
		}

		fclose(f);

	} else {

		fprintf(stderr, "ERROR: cannot read file: \"%s\"\n", file_name);

		exit(1);
	}

	return code;
}
