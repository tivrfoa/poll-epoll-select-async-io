#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

#define   LOCK_EX   2    /* exclusive lock */

int main() {
	FILE* fp = fopen("myfile.txt", "a");
	int result = flock(fileno(fp), LOCK_EX);

	fprintf(fp, "before sleep\n");
	sleep(10);
	fprintf(fp, "after 10 seconds\n");

	fclose(fp);

	return 0;
}
