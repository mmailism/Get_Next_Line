#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <fcntl.h>

int	main()
{
	int	fd;

	fd = open("file.txt", O_RDWR | O_CREAT | O_APPEND);

	dup2(fd, 1);

	write(1, "hello", 5);
	write(1, "\n", 1);

	return 0;
}
