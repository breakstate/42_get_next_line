#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char buf[10];
	int r;
	int fd = 0;
	fd = open("read_test.txt", O_RDONLY);
	r = 0;
	int count = 0;
	while (count < 5)
	{
		r = read(fd, buf, 5);
		printf("r - %d\n", r);
		count++;
	}
	return (0);
}
