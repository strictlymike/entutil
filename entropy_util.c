/* File: entropy_util.c
   Author: Michael Bailey
   License: WTFPL - http://www.wtfpl.net/
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "entropy_measurement.h"

void usage(char *progname)
{
	printf("Usage: %s filename\n", progname);
}

int main(int argc, char **argv, char **envp)
{
	int		fd;
	struct stat	st;
	int		iret;
	unsigned char	*buf;
	long double	entropy = -1;

	if (argc != 2) {
		usage(argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	iret = fstat(fd, &st);
	if (iret == -1) {
		perror("fstat");
		return 1;
	}

	buf = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (buf == MAP_FAILED) {
		perror("mmap");
		return 1;
	}

	ent_init();

	if (ent_by_bit(&entropy, buf, st.st_size) < 0) {
		fprintf(stderr, "Failed to calculate entropy\n");
	}

	// printf("Bitwise entropy: %Lf / %Lf\n", entropy, ent_by_bit_max);
	printf("%Lf", entropy);

	if (ent_by_nibble(&entropy, buf, st.st_size) < 0) {
		fprintf(stderr, "Failed to calculate entropy\n");
	}

	// printf("Nibble-wise entropy: %Lf / %Lf\n", entropy, ent_by_nibble_max);
	printf(" %Lf", entropy);

	if (ent_by_byte(&entropy, buf, st.st_size, 0) < 0) {
		fprintf(stderr, "Failed to calculate entropy\n");
	}

	// printf("Byte-wise entropy: %Lf / %Lf\n", entropy, ent_by_byte_max);
	printf(" %Lf\n", entropy);

	return 0;
}
