#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>

#include "load.h"

#define TEMP_FILE ".tmpfile"

void load_error(char *err_msg, char *filename);

void read_stdin(FILE *f);

uint8_t *load_file(char *filename) {

	FILE *f;
	struct stat st;
	uint8_t *code;

	code = NULL;

	f = fopen(filename, "r");

	if (f) {

		fstat(fileno(f), &st); // fileno() returns the file descriptor number // gets status information about the file specified by the open file descriptor and stores it

		if (st.st_size) { // malloc(0) // if ((st.st_size) == 0) return NULL

			code = malloc(st.st_size); // allocate space for the array
			fread(code, sizeof(*code), st.st_size, f); // reads data from the stream into the array pointed to, by pointer
		}

		fclose(f);

	} else {

		load_error("cannot read file", filename);
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

		load_error("cannot write file", filename);
	}

	return code;
}

void read_stdin(FILE *f) {

	int ch;

	while ((ch = getchar()) != EOF) {

		fputc(ch, f);
	}

	/*
	if (!feof(stdin)) {

		fprintf(stderr, "ERROR: did not complete reading stdin\n");

		exit(1);
	}
	*/
}

void load_error(char *err_msg, char *filename) {

	fprintf(stderr, "ERROR: %s: \"%s\"\n", err_msg, filename);

	exit(1);
}
