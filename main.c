#include "get_next_line.h"
#include <fcntl.h>

int main()
{
	int fd;
	char **line;
	int i;

	//need to malloc line
	fd = open("test", O_RDONLY);
	i = get_next_line(fd, line);
	return (0);
}
