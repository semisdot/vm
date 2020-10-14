#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>

#include "load.h"

#define TEMP_FILE ".tmpfile"

void read_stdin(FILE *f);

uint8_t *load_file(char *filename) {

	FILE *f;
	struct stat st;
	uint8_t *code;

	code = NULL;

	f = fopen(filename, "r");

	if (f) {

		fstat(fileno(f), &st); // fileno() returns the file descriptor number // gets status information about the file specified by the open file descriptor and stores it

		if (st.st_size) { // malloc(0)

			code = malloc(st.st_size); // allocate space for the array
			fread(code, sizeof(*code), st.st_size, f); // reads data from the stream into the array pointed to, by pointer
		}

		fclose(f);

	} else {

		fprintf(stderr, "ERROR: cannot read file: \"%s\"\n", filename);

		exit(1);
	}

	return code;
}

// create a temp file, load stdin in it and use load_file()
uint8_t *load_stdin(void) {

	FILE *f;
	char *filename;
	uint8_t *code;

	code = NULL;
	filename = TEMP_FILE;

	f = fopen(filename, "w");

	if (f) {

		read_stdin(f);
		fclose(f);
		code = load_file(filename);
		remove(filename);

	} else {

		fprintf(stderr, "ERROR: cannot write file: \"%s\"\n", filename);

		exit(1);
	}

	return code;
}

void read_stdin(FILE *f) {

	int ch;

	while ((ch = getchar()) != EOF) {

		fprintf(f, "%c", ch);
	}

	/*
	if (!feof(stdin)) {

		fprintf(stderr, "ERROR: did not complete reading stdin\n");

		exit(1);
	}
	*/
}
