// Async IO example: https://www.youtube.com/watch?v=wJGd7tKF2zY

#include <aio.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 25000

struct aiocb* async_read(FILE* fp, char* buf, int bytes) {
	struct aiocb* aio = malloc(sizeof(struct aiocb));
	if (aio == NULL) {
		return NULL;
	}

	memset(aio, 0, sizeof(*aio));

	aio->aio_buf = buf;
	aio->aio_fildes = fileno(fp);
	aio->aio_nbytes = bytes;
	aio->aio_offset = 0;

	int result = aio_read(aio);

	if (result < 0) {
		free(aio);
		return NULL;
	}

	return aio;
}

int main(int argc, char* argv[]) {
	int ret;
	FILE* fp;

	if (argc < 2) {
		printf("usage: %s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		perror("fopen");
		return EXIT_FAILURE;
	}

	char buf[BUFSIZE];
	struct aiocb* aio = async_read(fp, buf, BUFSIZE);

	uint64_t counter = 0;
	while (aio_error(aio) == EINPROGRESS) {
		++counter;
	}

	ret = aio_return(aio);

	fclose(fp);

	printf("While we were reading, we counted up %lu times.\n", counter);
	if (ret > 0) {
		printf("Got %d bytes:\n", ret);
	} else {
		printf("READ FAILED!!!\n");
	}

	return 0;
}
