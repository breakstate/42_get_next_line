#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_struct{
		int a;
		char *buff;
}				t_struct;

static int return_int()
{
	static t_struct ob;
	if (!ob.buff)
	{
		printf("if\n");
		ob.buff = malloc(20);
		bzero(ob.buff,20);
	}
	ob.buff[ob.a] = 'a';
	printf("buff - %s\n", ob.buff);
	ob.a = ob.a + 1;
	return (ob.a);
}


int main()
{
	int i;
	i = 5;
	while (i > 0)
	{
		printf("a - %d\n", return_int());
		i--;
	}
	return (0);
}
