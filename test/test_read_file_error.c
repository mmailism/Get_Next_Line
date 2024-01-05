#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

// static	==> 71.1 71.2


// open
// read
// BFS

// valgrind  4 type
// free
// structure


char	*gnl(int fd)
{

	static int	read_file;
	static char	*buffer;
	static char	*s;

	printf("==fd==%d\n",fd);
	buffer = (char *)malloc(BUFFER_SIZE +1);  // no Malloc read_file -1 (error)
	read_file = read(fd ,buffer, BUFFER_SIZE ); // strncpy
	printf("\nread_file=%d\nbuffer=%s\ns1=%s", read_file, buffer, s);

	s = buffer;
	printf("s2=%s\n",s);
	// free (buffer);
	return (s);
}

int	main(void)
{
	int	fd = open("59text.txt", O_RDONLY);
	


	printf("\n==main==%s\n", gnl(fd));
	close (fd);
	return(0);
}



/*

	char	*s;
	while (  (s=gnl(fd)) != NULL)
	{
		printf("		main==%s==",s );
	//	free (s);
	//	s = NULL;
	}	
	close (fd);
	return (0);
}
*/

/*
int	main(void)  
{
	int	fd;
	int	read_file;
	char	*buffer;

	fd = open("58text.txt", O_RDONLY);
	printf("\nfd=%d", fd);

	fd = open("59text.txt", O_RDONLY);
	printf("\nfd=%d", fd);


	printf("\n\nBUFFER_SIZE=%d", BUFFER_SIZE);

	read_file = read(fd ,buffer, BUFFER_SIZE );
	printf("\n\nread_file=%d\nbuffer=%s", read_file, buffer);

	read_file = read(fd ,buffer, BUFFER_SIZE );
	printf("\n\nread_file=%d\nbuffer=%s", read_file, buffer);
	
	close (fd);
}
*/

/*
	BFS = 10
  	abcd
  	efgh
  	i
*/

