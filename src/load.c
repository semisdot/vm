#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>

#include "load.h"

/* ---------------------------------------------------------------------------------------------------- */

static uint8_t *_load_stdin(FILE *stream);

static uint8_t *read_file(FILE *stream);
static void read_stdin(FILE *stream);

static void error_fopen(const char *filename);

/* ---------------------------------------------------------------------------------------------------- */

uint8_t *load_file(const char *filename) {

	uint8_t *code;

	{
		FILE *f;

		f = fopen(filename, "r");

		if (!f) {

			error_fopen(filename);
		}

		code = read_file(f);

		fclose(f);
	}

	return code;
}

uint8_t *load_stdin(void) {

	uint8_t *code;

	{
		FILE *f;

		f = tmpfile();

		if (!f) {

			error_fopen("tmp file");
		}

		code = _load_stdin(f);

		fclose(f);
	}

	return code;
}

/* ---------------------------------------------------------------------------------------------------- */

static uint8_t *_load_stdin(FILE *stream) {

	uint8_t *code;

	read_stdin(stream);

	rewind(stream); // fseek(stream, 0, SEEK_SET)
	code = read_file(stream);

	return code;
}

/* ---------------------------------------------------------------------------------------------------- */

static uint8_t *read_file(FILE *stream) {

	uint8_t *code;

	code = NULL;

	{
		struct stat st;

		fstat(fileno(stream), &st); // fileno() returns the file descriptor number // gets status information about the file specified by the open file descriptor and stores it

		if (st.st_size) { // malloc(0) // if (st.st_size == 0) return NULL

			code = malloc(st.st_size); // allocate space for the array
			fread(code, sizeof(*code), st.st_size, stream); // reads data from the stream into the array pointed to, by pointer
		}
	}

	return code;
}

static void read_stdin(FILE *stream) {

	int chr;

	while ((chr = getchar()) != EOF) {

		fputc(chr, stream);
	}
}

/* ---------------------------------------------------------------------------------------------------- */

static void error_fopen(const char *filename) {

	perror(filename);

	exit(1);
}
