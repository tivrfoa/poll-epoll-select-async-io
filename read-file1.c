#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* fp = fopen("myfile.txt", "r");

	if (fp == NULL) {
		printf("Error (%d) opening file ...\n", errno);
		return -1;
	}

	char buf[20];
	while (fscanf(fp, "%s", buf) == 1) {
		printf("%s\n", buf);
	}

	fclose(fp);

	return 0;
}
